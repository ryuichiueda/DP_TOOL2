#ifndef _HAND_H__
#define _HAND_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "Part.h"
#include "Coordinate.h"
using namespace std;

class Hand : public Part{
/*
               side length 
              |-----
    base      |
    length    |
              |-----
*/
private:
	double m_base_length;
	double m_side_length;
public:
	Hand(double base_length,double side_length);
	virtual ~Hand();
	Coordinate getEndPosition(Coordinate prev_pos,double prev_angle);
	virtual bool setAngle(double a);
};

#endif
