#include "StateTrans.h"
using namespace std;

StateTrans::StateTrans(){}

bool StateTrans::setStateNum(const string &str){
	m_state_num = atoi(str.c_str());
	if(m_state_num <= 0)
		return false;

	if(m_states.size() > 0)
		return false;

	m_states.reserve(m_state_num);
	return true;
}

int StateTrans::getStateNum(void){return m_state_num;}

bool StateTrans::setAction(const string &action){
	m_actions.push_back(action);
	return true;
}

bool StateTrans::setResolution(const string &word){
	m_resolution = atoi(word.c_str());
	return (m_resolution > 0);
}

void StateTrans::status(void){
	cerr << "statenum: " << m_state_num << endl;
	cerr << "actions: ";
	for(auto i=m_actions.begin();i<m_actions.end();i++){
		cerr << *i << " ";
	}
	cerr << endl;
	cerr << "resolution: " << m_resolution << endl;
}

State* StateTrans::getState(int num){
	return &m_states.at(num);
}

unsigned int StateTrans::getActionIndex(string &line){
	for(unsigned int i=0;i<m_actions.size();i++){
		if(m_actions[i] == line)
			return i;
	}
	return -1;
}

bool StateTrans::setStateTrans(int s,int a,int s_to,double p){
	return true;
}
