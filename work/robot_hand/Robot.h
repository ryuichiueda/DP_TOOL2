#ifndef _ROBOT_H__
#define _ROBOT_H__

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include "Part.h"
#include "Coordinate.h"
using namespace std;

class Action;

class Robot{
private:
	vector<Part*> m_arms;
	vector<Action> m_actions;

	int getStateNum(void);

	void getEachStateNum(int index,deque<int> *res);
	void writeStateTransition(int index,deque<int> *s,Action *a);

	int getStateIndex(vector<int> *s);

	bool isFinalState(int index,double x,double y,double r);
public:

	Robot();
	virtual ~Robot();

	Part *getPart(int index);
	void setPart(Part *a);
	Coordinate getEndPosition(void);
	int getEndAngle(void);

	//bool stateTrans(vector<int> *s,int a,vector<int> *ps);
	string &getActionName(int index);

	void writeHeader(void);
	void writeStateTransition(void);
	void writeFinalStates(double x,double y,double r);
};

#endif
