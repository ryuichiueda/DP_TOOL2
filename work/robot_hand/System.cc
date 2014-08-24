#include "System.h"
#include "Action.h"
#include "Arm.h"
#include "Hand.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

System::System(Target *ball)
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

	m_target = ball;
	//setup of state space and system
	m_parts.push_back(new Arm("arm0",100,0,180));
	m_parts.push_back(new Arm("arm1",100,-160,160));
	m_parts.push_back(new Hand(30,30));
}
System::~System()
{
	for(auto &i : m_parts){
		delete i;
	}
}

Part *System::getPart(int index){
	if(index >= 0 && index < (int)m_parts.size())
		return m_parts.at(index);

	return NULL;
}
void System::setPart(Part *a){m_parts.push_back(a);}

Coordinate System::getEndPosition(void)
{
	Coordinate c{0.0,0.0};
	double ang = 0.0;

	for(auto i=m_parts.begin();i<m_parts.end();i++){
		c = (*i)->getEndPosition(c,ang);
		ang += (*i)->getAngle();
	}

	return c;
}

int System::getEndAngle(void)
{
	int ang = 0;
	for(auto i=m_parts.begin();i<m_parts.end();i++){
		ang += (*i)->getAngle();
	}
	return ang;
}

/*
bool System::stateTrans(vector<int> *s,int a,vector<int> *ps)
{
	return m_actions.at(a).stateTrans(this,s,ps);
}
*/

/*
string &System::getActionName(int index)
{
	return m_actions.at(index).getName();
}
*/

int System::getStateNum(void)
{
	int n = 1;
	for(auto i=m_parts.begin();i<m_parts.end();i++){
		n *= (*i)->getStateNum();
	}
	return n;
}

void System::writeHeader(void)
{
	cout << "%%metadata%%" << endl;
	cout << "statenum " << getStateNum() << endl;
	
	cout << "actions";
	for(auto i=m_actions.begin();i<m_actions.end();i++)
		cout << " " << (*i).getName();

	cout << endl;
}

void System::writeStateTransition(void)
{
	cout << "%%state transitions%%" << endl;
	for(int i=0;i<getStateNum();i++){
		deque<int> s;
		getEachStateNum(i,&s);

		Arm *p = (Arm *)m_parts.at(0);
		p->setAngle(p->indexToAngle(s[0]));
		p = (Arm *)m_parts.at(1);
		p->setAngle(p->indexToAngle(s[1]));
		if(collisionWithTarget())
				continue;

		for(auto a=m_actions.begin();a<m_actions.end();a++){
			//state transition
			writeStateTransition(i,&s,&(*a));
		}
	}
}

void System::getEachStateNum(int index,deque<int> *res)
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

int System::getStateIndex(vector<int> *s)
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

void System::writeStateTransition(int index,deque<int> *s,Action *a)
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

	if(collisionWithTarget()){
		return;
	}


	int ps = getStateIndex(&posterior_state);

	cout << "state " << index << " action " << a->getName() << endl;
	cout << "\tstate " << ps << " prob. 1 cost 1000" << endl;
}

void System::writeFinalStates(void)
{
	ofstream ofs("./values.0");
	for(int i=0;i<getStateNum();i++){
		deque<int> s;
		getEachStateNum(i,&s);

		Arm *p = (Arm *)m_parts.at(0);
		p->setAngle(p->indexToAngle(s[0]));
		p = (Arm *)m_parts.at(1);
		p->setAngle(p->indexToAngle(s[1]));
		if(collisionWithTarget())
			continue;
		if(! isFinalState(i))
			continue;

		ofs << i << " " << 0 << endl;
	}
}

bool System::isFinalState(int index)
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

	double relative_x = m_target->x - pos.x;
	double relative_y = m_target->y - pos.y;

	double len = sqrt(relative_x * relative_x + relative_y * relative_y);
	double phi = atan2(relative_y, relative_x) - dir;

	double relative_x2 = len * cos(phi);
	double relative_y2 = len * sin(phi);

	return ((Hand *)m_parts.at(2))->isInside(relative_x2,relative_y2);
}

bool System::collisionWithTarget(Target *t)
{
	Coordinate prev_pos{0.0,0.0};
	double prev_ang{0.0};
	for(auto i=m_parts.begin();i!=m_parts.end();i++){
		if((*i)->collisionWithTarget(prev_pos,prev_ang,t))
			return true;

		prev_pos = (*i)->getEndPosition(prev_pos,prev_ang);
		prev_ang += (*i)->getAngle();
	}
	return false;
}

bool System::collisionWithTarget(void)
{
	return collisionWithTarget(m_target);
/*
	Coordinate prev_pos{0.0,0.0};
	double prev_ang{0.0};
	for(auto i=m_parts.begin();i!=m_parts.end();i++){
		if((*i)->collisionWithTarget(prev_pos,prev_ang,m_target))
			return true;

		prev_pos = (*i)->getEndPosition(prev_pos,prev_ang);
		prev_ang += (*i)->getAngle();
	}
	return false;
*/
}

bool System::readValues(int x,int y)
{
	stringstream ss;
	ss << "./ans/values." << x << "." << y << ".txt";
	ifstream ifs(ss.str());

	if(ifs.fail()){
		cerr << "no file" << endl;
		return true;
	}

	if(x < -150 || x > 150 || y < 0 || y > 150){
		cerr << "out of range" << endl;
		return true;
	}
	int ix = x + 150;

	auto &v = m_planned.m_value_func[ix][y];

	unsigned int state;
	long unsigned int v_tmp;
	const long unsigned int max = 65000;
	while(1){
		ifs >> state >> v_tmp;
		if(ifs.eof())
			break;

		if(state == v.size()){
			if(v_tmp > max)
				v.push_back(0);
			else
				v.push_back((unsigned short)v_tmp);
		}
		else if(state > v.size()){
			while(state != v.size()){
				v.push_back(0);//final state
			}
			if(v_tmp > max)
				v.push_back(0);
			else
				v.push_back((unsigned short)v_tmp);
		}
		else{
			return false;		
		}
	}
	return true;
}

bool System::readPolicy(void)
{
	stringstream ss;
	ss << "./ans/policy." << m_target->x << "." << m_target->y << ".txt";
	ifstream ifs(ss.str());

	unsigned int state;
	string action;

	m_policy.clear();

	while(1){
		ifs >> state >> action;
		if(ifs.eof())
			break;

		if(state == m_policy.size()){
			int a = getActionIndex(action);
			if(a < 0){
				return false;
			}
			m_policy.push_back(a);
		}
		else if(state > m_policy.size()){
			while(state != m_policy.size()){
				m_policy.push_back(-1);//final state
			}
			int a = getActionIndex(action);
			if(a < 0){
				return false;
			}
			m_policy.push_back(a);
		}
		else{
			return false;		
		}
	}

/*
	ofstream ofs("./hoge");
	for(unsigned int i=0;i<m_policy.size();i++){
		ofs << i << " " << m_policy[i] << endl;
	}
*/

	return true;
}

int System::getActionIndex(string &name)
{
	for(unsigned int i=0;i<m_actions.size();i++){
		if(m_actions[i].getName() == name){
			return (int)i;
		}
	}
	return -1;
}

bool System::doMotion(void)
{
	while(oneStepMotion()){
		for(auto &i : m_pf.m_particles){
			if(i.w < 0.00001)
				continue;
	
			Target t{i.x,i.y,m_target->radius};
			if(collisionWithTarget(&t)){
				i.w = 0.0;
			}
		}
	}

	vector<int> eachstate;
	for(auto &s : m_parts){
		eachstate.push_back(s->getState());
	}	
	int i = getStateIndex(&eachstate);

	draw(i);


	return isFinalState(i);
}

bool System::doPfcMotion(void)
{
	while(oneStepPfc()){
		for(auto &i : m_pf.m_particles){
			if(i.w < 0.00001)
				continue;
	
			Target t{i.x,i.y,m_target->radius};
			if(collisionWithTarget(&t)){
				i.w = 0.0;
			}
		}
	}

	vector<int> eachstate;
	for(auto &s : m_parts){
		eachstate.push_back(s->getState());
	}	
	int i = getStateIndex(&eachstate);

	draw(i);
	return isFinalState(i);
}

bool System::oneStepPfc(void)
{
	vector<int> eachstate;
	for(auto &s : m_parts){
		eachstate.push_back(s->getState());
	}	
	int i = getStateIndex(&eachstate);
	draw(i);

	cout << i;
	cerr << "!!" << endl;
	Action *a = NULL;
	if(m_policy[i] >= 0){
		a = &m_actions.at(m_policy[i]);
 		cout << " " << a->getName();
	}
	else
 		cout << " " << "final";

	for(unsigned int p=0;p<m_parts.size();p++){
		cout << " " << m_parts[p]->getAngle();
		if(a != NULL){
			int angle = m_parts[p]->getAngle() + a->getDelta(p);
			m_parts[p]->setAngle(angle);
		}
	}
	cout << endl;

	if(a == NULL)
		return false;

	return true;
}

bool System::oneStepMotion(void)
{
	vector<int> eachstate;
	for(auto &s : m_parts){
		eachstate.push_back(s->getState());
	}	
	int i = getStateIndex(&eachstate);
	draw(i);

	cout << i;
	Action *a = NULL;
	if(m_policy[i] >= 0){
		a = &m_actions.at(m_policy[i]);
 		cout << " " << a->getName();
	}
	else
 		cout << " " << "final";

	for(unsigned int p=0;p<m_parts.size();p++){
		cout << " " << m_parts[p]->getAngle();
		if(a != NULL){
			int angle = m_parts[p]->getAngle() + a->getDelta(p);
			m_parts[p]->setAngle(angle);
		}
	}
	cout << endl;

	if(a == NULL)
		return false;

	return true;
}

void System::draw(int state)
{
	static int counter = 0;

	stringstream ss;
	ss << "image/" << setfill('0') << setw(5) << counter << ".ppm";
	ofstream ofs(ss.str());
	counter++;

	const double mag = 0.8;
	const int cx = 200;
	const int cy = 50;
	const int size = 400;
	Pixel *image[size];
	for(int i=0;i<size;i++)
		image[i] = new Pixel[size];
	for(int y=size-1;y>=0;y--){
		for(int x=0;x<size;x++){
			image[x][y] = {255,255,255};
		}
	}	

	Coordinate pos{0.0,0.0};
	double ang{0.0};
	for(auto &s : m_parts){
		s->draw(size,image,mag,cx,cy,pos,ang);
		pos = s->getEndPosition(pos,ang);
		ang += s->getAngle();
	}	

	//ball
	for(int i=0;i<360;i++){
		double r = i*3.141592/180;
		int x = (int)((m_target->x + m_target->radius*cos(r))*mag) + cx;
		int y = (int)((m_target->y + m_target->radius*sin(r))*mag) + cy;
		image[x][y] = {255,0,0};
	}

	//particles
	for(auto &i : m_pf.m_particles){
		if(i.w < 0.1)
			continue;

		int x = (int)(i.x*mag + cx);
		int y = (int)(i.y*mag + cy);
		image[x][y] = {0,0,255};
	}

	ofs << "P3" << endl;
	ofs << size << " " << size << endl;
	ofs << "255" << endl;
	for(int y=size-1;y>=0;y--){
		for(int x=0;x<size;x++){
			ofs << (int)image[x][y].r << " ";
			ofs << (int)image[x][y].g << " ";
			ofs << (int)image[x][y].b << endl;
		}
	}	

	for(int i=0;i<size;i++)
		delete [] image[i];
}
