#ifndef _ROBOT_H__
#define _ROBOT_H__

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Coordinate{
	double x,y;
};

class Part{
protected:
	double m_angle;
public:
	Part();
	virtual ~Part();
	virtual Coordinate getEndPosition(Coordinate prev_pos,double prev_angle) = 0;
	virtual bool setAngle(double a) = 0;
	virtual double getAngle(void);
};

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
