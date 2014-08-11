#ifndef STATE_TRANS_H_
#define STATE_TRANS_H_

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
using namespace std;

class ActionTrans{
public:
	ActionTrans(string action_name){
		m_action_name = action_name;
	}
private:
	string m_action_name;
};

class State{
public:
	State(){}
private:
	vector<ActionTrans> m_actions;
};

class StateTrans{
public:
	StateTrans();
	bool setStateNum(const string &str);
	int getStateNum(void);
	bool setAction(const string &action);
	bool setResolution(const string &word);
	void status(void);
	State *getState(int num);
	unsigned int getActionIndex(string &line);
	bool setStateTrans(int s,int a,int s_to,double p);
private:
	int m_state_num;
	vector<string> m_actions;
	int m_resolution;
	vector<State> m_states;
};

#endif
