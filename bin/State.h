#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
using namespace std;


class State{
private:
	struct Transition{
		int posterior_state, probability, cost;
	};
	struct Action{
		vector<Transition> trans;
	};

	vector<Action> m_actions;
	int m_value;
public:
	State();
	bool setStateTrans(int a,int s_to,int p,int c,int action_num);
	int valueIteration(vector<State> &other_state, int resolution);
	int valueIterationAction(int a, vector<State> &other_state,int resolution);
	void setValue(int v);
	int getValue(void){return m_value;}
};

#endif
