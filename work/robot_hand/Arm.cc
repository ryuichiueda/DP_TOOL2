#include "Arm.h"
using namespace std;

Arm::Arm(string name, double length,double angle_min, double angle_max,double discrete_width) : Part()
{
	m_name = name;
	m_length = length;
	m_angle_max = angle_max;
	m_angle_min = angle_min;
	m_discrete_width = discrete_width;

	for(double ang=m_angle_min;ang<m_angle_max;ang+=discrete_width){
		m_discrete_states.push_back(ang);
	}
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

double Arm::stateToAngleDeg(int index)
{
	try{
		return m_discrete_states.at(index);
	}
	catch (const out_of_range& oor) {
		cerr << "Out of Range:" << endl;
		cerr << "\tname: " <<  m_name << endl;
		cerr << "\tsize: " <<  m_discrete_states.size() << endl;
		cerr << "\tindex: " <<  index << endl;
		throw oor;
	}
}
