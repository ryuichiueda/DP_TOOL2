#ifndef _ROBOT_H__
#define _ROBOT_H__

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include "Part.h"
#include "Structs.h"
using namespace std;

class Action;
class Target;

class Robot{
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

	bool oneStepMotion(void);

	void draw(int state);
public:

	Robot(Target *target);
	virtual ~Robot();

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

	//functions for simulation
	bool doMotion(void);
};

#endif
