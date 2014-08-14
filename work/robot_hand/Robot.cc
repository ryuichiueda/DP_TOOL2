#include "Robot.h"
#include "Action.h"
#include "Arm.h"
#include "Hand.h"
#include <fstream>
using namespace std;

Robot::Robot()
{
	//set of actions
	vector<int> rr{-1,-1}, rn{-1,0}, rl{-1,1},
			nr{0,-1}, nl{0,1},
			lr{1,-1}, ln{1,0}, ll{1,1};
	m_actions.push_back(Action("rr",&rr));
	m_actions.push_back(Action("rn",&rn));
	m_actions.push_back(Action("rl",&rl));
	m_actions.push_back(Action("nr",&nr));
	m_actions.push_back(Action("nl",&nl));
	m_actions.push_back(Action("lr",&lr));
	m_actions.push_back(Action("ln",&ln));
	m_actions.push_back(Action("ll",&ll));
}
Robot::~Robot(){}

Part *Robot::getPart(int index){
	if(index >= 0 && index < m_arms.size())
		return m_arms.at(index);

	return NULL;
}
void Robot::setPart(Part *a){m_arms.push_back(a);}

Coordinate Robot::getEndPosition(void)
{
	Coordinate c{0.0,0.0};
	double ang = 0.0;

	for(auto i=m_arms.begin();i<m_arms.end();i++){
		c = (*i)->getEndPosition(c,ang);
		ang += (*i)->getAngle();
	}

	return c;
}

int Robot::getEndAngle(void)
{
	int ang = 0;
	for(auto i=m_arms.begin();i<m_arms.end();i++){
		ang += (*i)->getAngle();
	}
	return ang;
}

/*
bool Robot::stateTrans(vector<int> *s,int a,vector<int> *ps)
{
	return m_actions.at(a).stateTrans(this,s,ps);
}
*/

string &Robot::getActionName(int index)
{
	cerr << m_actions.size() << endl;
	return m_actions.at(index).getName();
}

int Robot::getStateNum(void)
{
	int n = 1;
	for(auto i=m_arms.begin();i<m_arms.end();i++){
		n *= (*i)->getStateNum();
	}
	return n;
}

void Robot::writeHeader(void)
{
	cout << "%%metadata%%" << endl;
	cout << "statenum " << getStateNum() << endl;
	
	cout << "actions";
	for(auto i=m_actions.begin();i<m_actions.end();i++)
		cout << " " << (*i).getName();

	cout << endl;
}

void Robot::writeStateTransition(void)
{
	cout << "%%state transitions%%" << endl;
	for(int i=0;i<getStateNum();i++){
		deque<int> s;
		getEachStateNum(i,&s);

		for(auto a=m_actions.begin();a<m_actions.end();a++){
			//state transition
			writeStateTransition(i,&s,&(*a));
		}
	}
}

void Robot::getEachStateNum(int index,deque<int> *res)
{
	int carry = index;
	for(auto i=m_arms.rbegin();i!=m_arms.rend();i++){
		int n = (*i)->getStateNum();
		if(n < 2)
			continue;

		res->push_front(carry%n);
		carry = carry/n;
	}
}

int Robot::getStateIndex(vector<int> *s)
{
	int index = 0;
	for(int i=0;i<m_arms.size();i++){
		if(m_arms.at(i)->getStateNum() < 2){
			continue;
		}

		index *= m_arms.at(i)->getStateNum();
		index += s->at(i);
	}
	return index;
}

void Robot::writeStateTransition(int index,deque<int> *s,Action *a)
{
	vector<int> posterior_state;
	for(int i=0;i<s->size();i++){
		int ps = s->at(i) + a->getDelta(i);
		if(! ((Arm*)m_arms.at(i))->inRange(ps))
			return;
			
		posterior_state.push_back(ps);
	}
	cout << "state " << index << " action " << a->getName() << endl;
	cout << "\tstate " << getStateIndex(&posterior_state);
	cout << " prob. 1 cost 1000" << endl;
}

void Robot::writeFinalStates(double x,double y,double r)
{
	ofstream ofs("./values.0");
	for(int i=0;i<getStateNum();i++){
		if(isFinalState(i,x,y,r)){
			ofs << i << " " << 0 << endl;
		}
	}
}

bool Robot::isFinalState(int index,double x,double y,double r)
{
	//hard coding 
	//it should be improved
	deque<int> s;
	getEachStateNum(index,&s);
	Arm *p = (Arm *)m_arms.at(0);
	p->setAngle(p->indexToAngle(s.at(0)));
	p = (Arm *)m_arms.at(1);
	p->setAngle(p->indexToAngle(s.at(1)));

	Coordinate pos = getEndPosition();
	double dir = getEndAngle()/180.0*3.141592;

	cerr << index << " " << pos.x << " " << pos.y << endl;

	double relative_x = x - pos.x;
	double relative_y = y - pos.y;

	double len = sqrt(relative_x * relative_x + relative_y * relative_y);
	double phi = atan2(relative_y, relative_x) - dir;

	double relative_x2 = len * cos(phi);
	double relative_y2 = len * sin(phi);

	return ((Hand *)m_arms.at(2))->isInside(relative_x2,relative_y2);
}
