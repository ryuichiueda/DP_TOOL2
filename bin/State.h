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
		unsigned int probability;
		unsigned long posterior_state, cost;
	};
	struct Action{
		vector<Transition> trans;
	};

	vector<Action> m_actions;
	unsigned long m_value;
public:
	State();
	~State();
	bool setStateTrans(int a,unsigned long s_to,unsigned int p,unsigned long c,int action_num);
	unsigned long valueIteration(vector<State> &other_state);
	unsigned long valueIterationAction(int a, vector<State> &other_state);
	void setValue(unsigned long v);
	unsigned long getValue(void){return m_value;}
};

#endif
