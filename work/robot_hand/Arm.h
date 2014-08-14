#ifndef _ARM_H__
#define _ARM_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "Part.h"
#include "Coordinate.h"
using namespace std;

class Arm : public Part{
private:
	string m_name;
	int m_length;
	int m_angle_max;
	int m_angle_min;

public:
	Arm(string name, int length, int angle_min, int angle_max);
	virtual ~Arm();
	Coordinate getEndPosition(Coordinate prev_pos,int prev_angle);
	virtual bool setAngle(int a);
	int indexToAngle(int i);
	virtual int getStateNum(void);

	double stateToAngleDeg(int index);

	bool inRange(int index);
};

#endif
