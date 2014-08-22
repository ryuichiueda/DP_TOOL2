#ifndef _ROBOT_H__
#define _ROBOT_H__

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include "ParticleFilter.h"
#include "Structs.h"
using namespace std;

class Part;
class Action;
struct Target;
class ParticleFilter;

class PlannedResult{
public:
	vector<int> m_policy;
	vector<unsigned short> *m_value_func[301];

	PlannedResult()
	{
		for(int i=0;i<301;i++)
			m_value_func[i] = new vector<unsigned short>[151];
	}
	~PlannedResult()
	{
		for(int i=0;i<301;i++)
			delete [] m_value_func[i];
	}
};

class System{
private:
	vector<Part*> m_parts;
	vector<Action> m_actions;

	Target *m_target;

	int getStateNum(void);

	void getEachStateNum(int index,deque<int> *res);
	void writeStateTransition(int index,deque<int> *s,Action *a);

	int getStateIndex(vector<int> *s);

	bool isFinalState(int index);

	vector<int> m_policy;
	PlannedResult m_planned;

	bool oneStepMotion(void);
	bool oneStepPfc(void);

	void draw(int state);

	//particle filter
	ParticleFilter m_pf;

public:
	System(Target *ball);
	virtual ~System();

	Part *getPart(int index);
	void setPart(Part *a);
	Coordinate getEndPosition(void);
	int getEndAngle(void);

	//bool stateTrans(vector<int> *s,int a,vector<int> *ps);
	//string &getActionName(int index);
	int getActionIndex(string &name);

	void writeHeader(void);
	void writeStateTransition(void);
	void writeFinalStates(void);

	bool collisionWithTarget(void);

	bool readPolicy(void);
	bool readValues(int x, int y);

	//functions for simulation
	bool doMotion(void);
	bool doPfcMotion(void);
};

#endif
