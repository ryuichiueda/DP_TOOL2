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

void die(string reason){
	cerr << "value_iteration: [ERROR] " << reason << endl;
	exit(1);
}

void worker(int start_pos,StateTrans *st) {
	//no need of exclusive control due to the property of value functions
	st->valueIteration(start_pos);
}

int main(int argc, char const* argv[])
{
	StateTrans evaluator;

	int worker_num = 1;
	int filename_pos = 1;

	if(argc < 2){
		usage();
	}
	else if(argc == 4){
		filename_pos = 3;
		worker_num = atoi(argv[2]);

		if(worker_num <= 0)
			die("Invalid Thread Num");
	}

	if(! evaluator.readStateTransFile(argv[filename_pos]))
		die("state_trans file error");

	if(worker_num == 1){
		evaluator.valueIteration(0);
		evaluator.printAllValues();
		exit(0);
	}

	vector<thread> th;
	for(int i=0;i<worker_num;i++){
		unsigned long start_pos = (unsigned long)
			(double(evaluator.getStateNum())/worker_num*i);

		th.push_back(thread(worker,start_pos,&evaluator));
	}

	for(int i=0;i<worker_num;i++){
		th[i].join();
	}

	evaluator.printAllValues();

	exit(0);
}


