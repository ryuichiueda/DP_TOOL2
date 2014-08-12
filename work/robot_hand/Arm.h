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
	double m_length;
	double m_angle_max;
	double m_angle_min;
public:
	Arm(double length,double angle_min, double angle_max);
	virtual ~Arm();
	Coordinate getEndPosition(Coordinate prev_pos,double prev_angle);
	virtual bool setAngle(double a);
};

#endif
