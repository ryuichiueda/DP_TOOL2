#ifndef _ACTION_H__
#define _ACTION_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "Part.h"
#include "Coordinate.h"
using namespace std;

class Robot;

class Action{
private:
	vector<int> m_deltas;
	string m_name;
public:
	Action(string name,vector<int> *deltas);
	//bool stateTrans(Robot *r,vector<int> *s,vector<int> *ps);
	string &getName(void);
	int getDelta(int index);
};

#endif
