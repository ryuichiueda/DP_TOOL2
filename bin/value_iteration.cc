#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "StateTrans.h"
using namespace std;

bool parserHeader(string &line);
bool parserStateTrans(string &line);
void usage(void);
void die(string);
bool tokenizer(string &line,vector<string> &words);

StateTrans g_state_trans;

int main(int argc, char const* argv[])
{
	if(argc < 2)
		usage();

	ifstream ifs_state_trans(argv[1]);
	string buf;

	//parse of header in state transition file
	while(ifs_state_trans && getline(ifs_state_trans,buf)){
		if(parserHeader(buf) == false)
			break;
	}
	g_state_trans.status();

	//parse of state transtions in state transition file
	while(ifs_state_trans && getline(ifs_state_trans,buf)){
		if(parserStateTrans(buf) == false)
			break;
	}

	return 0;
}

bool parserHeader(string &line){
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

bool parserStateTrans(string &line){
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

		if(s_after < 0)
			die("Invalid Posterior State");
		if(p <= 0.0 || p > 1.0)
			die("Invalid Probability");

		g_state_trans.setStateTrans(state_index,action_index,s_after,p);

	}

	return true;
}

void usage(void){
	cerr << "\tvalue_iteration" << endl;	
	cerr << "\tdate: Mon Aug 11 12:31:24 JST 2014" << endl;	
	cerr << "\twritten by: Ryuichi Ueda" << endl;
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
