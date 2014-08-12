#include "Hand.h"
using namespace std;

Hand::Hand(double base_length,double side_length) : Part()
{
	m_base_length = base_length;
	m_side_length = side_length;
}

Hand::~Hand(){}

bool Hand::setAngle(double a)
{
	return false;
}

Coordinate Hand::getEndPosition(Coordinate prev_pos,double prev_angle)
{
	//Hand does not have the definition of end point.
	return prev_pos;
}

/*
Robot::Robot(){}
Robot::~Robot(){}

Part *Robot::getPart(int index){return m_arms.at(index);}
void Robot::setPart(Part *a){m_arms.push_back(a);}

Coordinate Robot::getEndPosition(void)
{
	Coordinate c{0.0,0.0};
	double ang = 0.0;

	for(auto i=m_arms.begin();i<m_arms.end();i++){
		c = (*i)->getEndPosition(c,ang);
		ang += (*i)->getAngle();
	}

	return c;
}

double Robot::getEndAngle(void)
{
	double ang = 0.0;
	for(auto i=m_arms.begin();i<m_arms.end();i++){
		ang += (*i)->getAngle();
	}
	return ang;
}

*/
