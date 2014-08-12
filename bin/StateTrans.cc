#include "StateTrans.h"
#include <climits>
using namespace std;

StateTrans::StateTrans(){}

bool StateTrans::setStateNum(const string &str)
{
	m_state_num = atoi(str.c_str());
	if(m_state_num <= 0)
		return false;

	if(m_states.size() > 0)
		return false;

	m_states.reserve(m_state_num);
	for(unsigned long i=0;i<m_state_num;i++){
		State s;
		s.setValue(m_value_limit);
		m_states.push_back(s);
	}
	return true;
}

unsigned long StateTrans::getStateNum(void)
{
	return m_state_num;
}

bool StateTrans::setAction(const string &action)
{
	m_actions.push_back(action);
	return true;
}

void StateTrans::status(void)
{
	cerr << "statenum: " << m_state_num << endl;
	cerr << "actions: ";
	for(auto i=m_actions.begin();i<m_actions.end();i++){
		cerr << *i << " ";
	}
	cerr << endl;
}

State* StateTrans::getState(unsigned long index)
{
	return &m_states.at(index);
}

unsigned int StateTrans::getActionIndex(string &line)
{
	for(unsigned int i=0;i<m_actions.size();i++){
		if(m_actions[i] == line)
			return i;
	}
	return -1;
}

bool StateTrans::setStateTrans(unsigned long s,int a,unsigned long s_to,double prob,unsigned long cost)
{
	return m_states[s].setStateTrans(a,s_to, (unsigned int)(prob*65536),
				cost,m_actions.size());
}

bool StateTrans::valueIteration(void)
{
	for(unsigned long i=0;i<m_state_num;i++){
		unsigned long v = m_states.at(i).valueIteration(m_states);
		cout << i << " " << v << endl;
	}
	return true;
}

bool StateTrans::setValue(unsigned long s,unsigned long v)
{
	m_states.at(s).setValue(v);
	
	return true;
}
