#ifndef _HAND_H__
#define _HAND_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "Part.h"
#include "Structs.h"
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

	vector<Coordinate> getEndPositions(Coordinate prev_pos,int prev_angle);
public:
	Hand(int base_length,int side_length);
	virtual ~Hand();
	Coordinate getEndPosition(Coordinate prev_pos,int prev_angle);
	virtual void setAngle(int a);
	virtual int getStateNum(void);

	bool isInside(double relative_x, double relative_y);
	virtual bool collisionWithBall(Coordinate prev_pos,int prev_angle,Target *target);

	virtual void draw(int size,Pixel *img[],double mag,int cx,int cy,Coordinate &pos,double ang);
};

#endif
