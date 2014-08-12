#ifndef _ROBOT_H__
#define _ROBOT_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "Part.h"
#include "Coordinate.h"
using namespace std;

/*
class Hand : public Part{
private:
	double m_base_length;
	double m_side_length;
public:
	Hand(double base_length,double side_length);
	virtual ~Hand();
	Coordinate getEndPosition(Coordinate prev_pos,double prev_angle);
	virtual bool setAngle(double a);
};
*/

class Robot{
private:
	vector<Part*> m_arms;
public:
	Robot();
	virtual ~Robot();

	Part *getPart(int index);
	void setPart(Part *a);
	Coordinate getEndPosition(void);
	double getEndAngle(void);
};

#endif