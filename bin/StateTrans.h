#ifndef STATE_TRANS_H_
#define STATE_TRANS_H_

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "State.h"
using namespace std;

class StateTrans{
private:
	unsigned long m_state_num;
	vector<string> m_actions;
	vector<State> m_states;

	const unsigned long m_value_limit = 70368744177664;//2^46

	bool parseHeader(string &line);
	bool parseStateTrans(string &line);
	bool tokenizer(string &line,vector<string> &words);
public:
	StateTrans();
	bool setStateNum(const string &str);
	unsigned long getStateNum(void);
	bool setAction(const string &action);
	void status(void);
	State *getState(unsigned long index);
	unsigned int getActionIndex(string &line);
	bool setStateTrans(unsigned long s,int a,unsigned long s_to,double p,unsigned long cost);
	bool setValue(unsigned long s,unsigned long v);

	bool valueIteration(unsigned long start_pos);

	void printAllValues(void);

	bool readStateTransFile(const char *filename);
};

#endif
