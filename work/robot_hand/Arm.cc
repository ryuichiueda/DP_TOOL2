#include "Arm.h"
using namespace std;

Arm::Arm(double length,double angle_min, double angle_max) : Part()
{
	m_length = length;
	m_angle_max = angle_max;
	m_angle_min = angle_min;
}

Arm::~Arm(){}

Coordinate Arm::getEndPosition(Coordinate prev_pos,double prev_angle)
{
	double ang = m_angle + prev_angle;	
	double x = prev_pos.x + m_length*cos(ang*3.141592/180.0);
	double y = prev_pos.y + m_length*sin(ang*3.141592/180.0);

	return Coordinate{x,y};
}

bool Arm::setAngle(double a)
{
	m_angle = a;
	return true;
}
