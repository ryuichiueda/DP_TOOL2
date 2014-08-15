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
	if(index >= 0 && index < (int)m_parts.size())
		return m_parts.at(index);

	return NULL;
}
void Robot::setPart(Part *a){m_parts.push_back(a);}

Coordinate Robot::getEndPosition(void)
{
	Coordinate c{0.0,0.0};
	double ang = 0.0;

	for(auto i=m_parts.begin();i<m_parts.end();i++){
		c = (*i)->getEndPosition(c,ang);
		ang += (*i)->getAngle();
	}

	return c;
}

int Robot::getEndAngle(void)
{
	int ang = 0;
	for(auto i=m_parts.begin();i<m_parts.end();i++){
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
	for(auto i=m_parts.begin();i<m_parts.end();i++){
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

void Robot::writeStateTransition(double bx,double by,double br)
{
	cout << "%%state transitions%%" << endl;
	for(int i=0;i<getStateNum();i++){
		deque<int> s;
		getEachStateNum(i,&s);

		Arm *p = (Arm *)m_parts.at(0);
		p->setAngle(p->indexToAngle(s[0]));
		p = (Arm *)m_parts.at(1);
		p->setAngle(p->indexToAngle(s[1]));
		if(collisionWithBall(bx,by,br))
				return;

		for(auto a=m_actions.begin();a<m_actions.end();a++){
			//state transition
			writeStateTransition(i,&s,&(*a),bx,by,br);
		}
	}
}

void Robot::getEachStateNum(int index,deque<int> *res)
{
	int carry = index;
	for(auto i=m_parts.rbegin();i!=m_parts.rend();i++){
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
	for(unsigned int i=0;i<m_parts.size();i++){
		if(m_parts.at(i)->getStateNum() < 2){
			continue;
		}

		index *= m_parts.at(i)->getStateNum();
		index += s->at(i);
	}
	return index;
}

void Robot::writeStateTransition(int index,deque<int> *s,Action *a,
	double bx,double by,double br)
{
	vector<int> posterior_state;
	for(unsigned int i=0;i<s->size();i++){
		int ps = s->at(i) + a->getDelta(i);
		Arm *p = (Arm*)m_parts.at(i);
		if(! p->inRange(ps))
			return;

		p->setAngle(p->indexToAngle(ps));

		posterior_state.push_back(ps);
	}
	if(collisionWithBall(bx,by,br))
			return;


	int ps = getStateIndex(&posterior_state);

	cout << "state " << index << " action " << a->getName() << endl;
	cout << "\tstate " << ps << " prob. 1 cost 1000" << endl;
}

void Robot::writeFinalStates(double x,double y,double r)
{
	ofstream ofs("./values.0");
	for(int i=0;i<getStateNum();i++){
		if(collisionWithBall(x,y,r))
			continue;
		if(! isFinalState(i,x,y,r))
			continue;

		ofs << i << " " << 0 << endl;
	}
}

bool Robot::isFinalState(int index,double x,double y,double r)
{
	//hard coding 
	//it should be improved
	deque<int> s;
	getEachStateNum(index,&s);
	Arm *p = (Arm *)m_parts.at(0);
	p->setAngle(p->indexToAngle(s.at(0)));
	p = (Arm *)m_parts.at(1);
	p->setAngle(p->indexToAngle(s.at(1)));

	Coordinate pos = getEndPosition();
	double dir = getEndAngle()/180.0*3.141592;

	double relative_x = x - pos.x;
	double relative_y = y - pos.y;

	double len = sqrt(relative_x * relative_x + relative_y * relative_y);
	double phi = atan2(relative_y, relative_x) - dir;

	double relative_x2 = len * cos(phi);
	double relative_y2 = len * sin(phi);

	return ((Hand *)m_parts.at(2))->isInside(relative_x2,relative_y2);
}

bool Robot::collisionWithBall(double x,double y,double r)
{
	Coordinate prev_pos{0.0,0.0};
	double prev_ang{0.0};
	for(auto i=m_parts.begin();i!=m_parts.end();i++){
		if((*i)->collisionWithBall(prev_pos,prev_ang,x,y,r))
			return true;

		prev_pos = (*i)->getEndPosition(prev_pos,prev_ang);
		prev_ang += (*i)->getAngle();
	}
	return false;
}
