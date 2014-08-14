#include "Hand.h"
using namespace std;

Hand::Hand(int base_length,int side_length) : Part()
{
	m_base_length = base_length;
	m_side_length = side_length;
}

Hand::~Hand(){}

bool Hand::setAngle(int a)
{//hand has no joint so nothing is set
	return false;
}

Coordinate Hand::getEndPosition(Coordinate prev_pos,int prev_angle)
{
	//Hand does not have the definition of end point.
	return prev_pos;
}

int Hand::getStateNum(void)
{
	return 1;
}

bool Hand::isInside(double relative_x, double relative_y)
{
	if(relative_x <= 0.0)
		return false;

	if(relative_x > m_side_length)
		return false;
	
	if(relative_y > m_base_length/2)
		return false;

	return true;
}
