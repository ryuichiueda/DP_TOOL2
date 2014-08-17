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

	m_discrete_state = 0;
	m_angle = m_angle_min;
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
	m_discrete_state = a - m_angle_min;
}

double Arm::stateToAngleDeg(int index)
{
	return m_discrete_states.at(index);
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

bool Arm::collisionWithBall(Coordinate prev_pos,int prev_angle,Target *target)
{
	Coordinate end_pos = getEndPosition(prev_pos,prev_angle);
	
	double dx = prev_pos.x - end_pos.x;
	double dy = prev_pos.y - end_pos.y;

	double t = ((target->x - end_pos.x)*dx + (target->y - end_pos.y)*dy)/(dx*dx + dy*dy);

	if(t < 0.0 || t > 1.0)
		return false;

	double a = end_pos.y - prev_pos.x;
	double b = prev_pos.x - end_pos.x;
	double c = (end_pos.x - prev_pos.x)*prev_pos.y - (end_pos.y - prev_pos.y)*prev_pos.x;

	double d = fabs(a*target->x + b*target->y + c)/sqrt(a*a + b*b);

	if(d > target->radius)
		return false;

	double x = target->x - prev_pos.x;
	double y = target->y - prev_pos.y;
	if(x*x + y*y > target->radius * target->radius)
		return false;

	x = target->x - end_pos.x;
	y = target->y - end_pos.y;
	if(x*x + y*y > target->radius * target->radius)
		return false;
 
	return true;
}

void Arm::draw(int size,Pixel *img[],double mag,int cx,int cy,Coordinate &pos,double ang)
{
	Coordinate end_pos = getEndPosition(pos,ang);
	
	double start_x = (double)cx + pos.x*mag;
	double start_y = (double)cy + pos.y*mag;
	double end_x = (double)cx + end_pos.x*mag;
	double end_y = (double)cy + end_pos.y*mag;

	for(int i=0;i<=size;i++){
		int x = int(start_x + (end_x - start_x)*(1.0 - ((double)i)/size));
		int y = int(start_y + (end_y - start_y)*(1.0 - ((double)i)/size));

		if(x < 0 || x >= size)
			continue;
		if(y < 0 || y >= size)
			continue;

		img[x][y] = {0,0,0};
	}
}
