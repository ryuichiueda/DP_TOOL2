#include "Action.h"
using namespace std;

Action::Action(string name,vector<int> *deltas)
{
	for(auto i=deltas->begin();i<deltas->end();i++)
		m_deltas.push_back(*i);

	m_name = name;
}

/*
bool Action::stateTrans(Robot *r,vector<int> *s,vector<int> *ps)
{
	ps = s;
	return true;
}
*/

string &Action::getName(void)
{
	return m_name;
}

int Action::getDelta(int index)
{
	return m_deltas.at(index);
}
