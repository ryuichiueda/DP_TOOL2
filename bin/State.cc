#include "State.h"
using namespace std;


State::State(){}

bool State::setStateTrans(int a,int s_to,int p,int c,int action_num)
{
	if(m_actions.size() == 0){
		Action act;
		for(int i=0;i<action_num;i++)
			m_actions.push_back(act);
	}

	Transition t{s_to,p,c};
	m_actions.at(a).trans.push_back(t);
	return true;
}

int State::valueIteration(vector<State> &other_state, int resolution)
{
	int v_min = 999999999;
	for(unsigned int a=0;a<m_actions.size();a++){
		if(m_actions.at(a).trans.size() == 0)
			continue;

		int v = valueIterationAction(a,other_state,resolution);
		if(v_min > v)
			v_min = v;
	}
	if(v_min < m_value)
		return v_min;
	else
		return m_value;
}

int State::valueIterationAction(int a,vector<State> &other_state, int resolution)
{
	auto *trans = &m_actions.at(a).trans;

	int v = 0;
	for(auto i=trans->begin();i<trans->end();i++){
		int tmp = other_state.at(i->posterior_state).getValue() + (i->cost)*resolution;
		v += (tmp * i->probability) / resolution;
	}
	return v;
}

void State::setValue(int v)
{
	m_value = v;
}
