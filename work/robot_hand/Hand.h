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
	int m_base_length;
	int m_side_length;
public:
	Hand(int base_length,int side_length);
	virtual ~Hand();
	Coordinate getEndPosition(Coordinate prev_pos,int prev_angle);
	virtual bool setAngle(int a);
	virtual int getStateNum(void);

	bool isInside(double relative_x, double relative_y);
};

#endif
