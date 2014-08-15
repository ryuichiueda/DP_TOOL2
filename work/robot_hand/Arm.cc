#include "Arm.h"
using namespace std;

Arm::Arm(string name, int length,int angle_min, int angle_max) : Part()
{
	m_name = name;
	m_length = length;
	m_angle_max = angle_max;
	m_angle_min = angle_min;

	for(int ang=m_angle_min;ang<=m_angle_max;ang++){
		m_discrete_states.push_back(ang);
	}
}

Arm::~Arm(){}

Coordinate Arm::getEndPosition(Coordinate prev_pos,int prev_angle)
{
	int ang = m_angle + prev_angle;	
	double x = prev_pos.x + m_length*cos(ang*3.141592/180.0);
	double y = prev_pos.y + m_length*sin(ang*3.141592/180.0);

	return Coordinate{x,y};
}

void Arm::setAngle(int a)
{
	m_angle = a;
}

double Arm::stateToAngleDeg(int index)
{
	return m_discrete_states.at(index);
/*
	catch (const out_of_range& oor) {
		cerr << "Out of Range:" << endl;
		cerr << "\tname: " <<  m_name << endl;
		cerr << "\tsize: " <<  m_discrete_states.size() << endl;
		cerr << "\tindex: " <<  index << endl;
		throw oor;
	}
*/
}

int Arm::getStateNum(void)
{
	return m_angle_max - m_angle_min + 1;
}

bool Arm::inRange(int index)
{
	int angle = index + m_angle_min;
	return (angle <= m_angle_max) && (angle >= m_angle_min);
}

int Arm::indexToAngle(int i)
{
	return i + m_angle_min;
}

bool Arm::collisionWithBall(Coordinate prev_pos,int prev_angle,
					double x,double y,double r)
{
	return false;
}
