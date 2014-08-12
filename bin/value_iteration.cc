#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "StateTrans.h"
#include <thread>
using namespace std;

void usage(void){
	cerr << "\tvalue_iteration" << endl;	
	cerr << "\tusage:\t./value_iteration [-p <n>] <state trans file>" << endl;	
	cerr << "\tdate:\tMon Aug 11 12:31:24 JST 2014" << endl;	
	cerr << "\twritten by Ryuichi Ueda" << endl;
	exit(1);
}

bool parseHeader(string &line);
bool parseStateTrans(string &line);
void die(string);
bool tokenizer(string &line,vector<string> &words);

StateTrans g_state_trans;

void worker(int start_pos) {
	g_state_trans.valueIteration(start_pos);
}


int main(int argc, char const* argv[])
{
	int worker_num = 1;
	int filename_pos = 1;

	if(argc < 2)
		usage();
	else if(argc == 4){
		filename_pos = 3;
		worker_num = atoi(argv[2]);

		if(worker_num <= 0)
			die("Invalid Thread Num");
	}

	ifstream ifs_state_trans(argv[filename_pos]);
	string buf;

	//parse of header in state transition file
	while(ifs_state_trans && getline(ifs_state_trans,buf)){
		if(parseHeader(buf) == false)
			break;
	}

	//checking global setting
	//g_state_trans.status();

	//parse of state transtions in state transition file
	while(ifs_state_trans && getline(ifs_state_trans,buf)){
		if(parseStateTrans(buf) == false)
			break;
	}

	ifs_state_trans.close();

	//read of state values
	while(! cin.eof()){
		unsigned long s,v;
		cin >> s >> v;
		g_state_trans.setValue(s,v);
	}

	if(worker_num == 1){
		g_state_trans.valueIteration(0);
	}

	vector<thread> th;
	for(int i=0;i<worker_num;i++){
		unsigned long start_pos = (unsigned long)
			(double(g_state_trans.getStateNum())/worker_num*i);
		th.push_back(thread(worker,start_pos));
	}

	for(int i=0;i<worker_num;i++)
		th[i].join();

	g_state_trans.printAllValues();

	exit(0);
}

bool parseHeader(string &line){
	if(line == "%%state transitions%%")
		return false;
	
	vector<string> words;
	tokenizer(line,words);
	if(words.size() < 1)
		return true;

	if(words.at(0) == "statenum"){
		if(! g_state_trans.setStateNum(words.at(1))){
			die("Invalid State Number");
		}
	}
	else if(words.at(0) == "actions"){
		for(auto i=++words.begin();i<words.end();i++){
			g_state_trans.setAction(*i);
		}	
	}

	return true;
}

bool parseStateTrans(string &line){
	vector<string> words;
	tokenizer(line,words);
	if(words.size() < 1)
		return true;

	static int state_index = -1;
	static int action_index = -1;
	if(words.at(0) == "state"){
		state_index = atoi(words.at(1).c_str());
		action_index = g_state_trans.getActionIndex(words.at(3));

		if(state_index < 0)
			die("Invalid State No.");
	}
	else if((words.at(0))[0] == '\t'){
		int s_after = atoi(words.at(1).c_str());
		double p = atof(words.at(3).c_str());
		double c = atof(words.at(5).c_str());

		if(s_after < 0)
			die("Invalid Posterior State");
		if(p <= 0.0 || p > 1.0)
			die("Invalid Probability");

		g_state_trans.setStateTrans(state_index,action_index,s_after,p,c);

	}

	return true;
}

void die(string reason){
	cerr << "value_iteration: [ERROR] " << reason << endl;
	exit(1);
}

bool tokenizer(string &line,vector<string> &words){
	string token;
	stringstream ss(line);
	while(getline(ss,token,' ')){
		words.push_back(token);
	}
	return true;
}
