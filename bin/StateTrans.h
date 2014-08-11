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
	int m_state_num;
	vector<string> m_actions;
	int m_resolution;
	vector<State> m_states;
public:
	StateTrans();
	bool setStateNum(const string &str);
	int getStateNum(void);
	bool setAction(const string &action);
	bool setResolution(const string &word);
	void status(void);
	State *getState(int num);
	unsigned int getActionIndex(string &line);
	bool setStateTrans(int s,int a,int s_to,double p,int cost);
	bool setValue(int s,int v);

	bool valueIteration(void);

};

#endif
