#include "State.h"
using namespace std;


State::State(){}

bool State::setStateTrans(int a,unsigned long s_to,unsigned int p,unsigned long c,int action_num)
{
	if(m_actions.size() == 0){
		Action act;
		for(int i=0;i<action_num;i++)
			m_actions.push_back(act);
	}

	Transition t{p,s_to,c};
	m_actions.at(a).trans.push_back(t);
	return true;
}

unsigned long State::valueIteration(vector<State> &other_state)
{
	unsigned long v_min = m_value;
	for(unsigned int a=0;a<m_actions.size();a++){
		if(m_actions.at(a).trans.size() == 0)
			continue;

		unsigned long v = valueIterationAction(a,other_state);
		if(v_min > v)
			v_min = v;
	}
	return v_min;
}

unsigned long State::valueIterationAction(int a,vector<State> &other_state)
{
	auto *trans = &m_actions.at(a).trans;

	unsigned long v = 0;
	for(auto i=trans->begin();i<trans->end();i++){
		unsigned long tmp = other_state.at(i->posterior_state).getValue() + (i->cost);
		v += tmp * i->probability;
	}
	return v >> 16;
}

void State::setValue(unsigned long v)
{
	m_value = v;
}
