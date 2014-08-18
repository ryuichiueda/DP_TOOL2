#include "System.h"
using namespace std;

Part::Part(){
	m_angle = 0.0;
	m_discrete_state = 0;
}
Part::~Part(){}

int Part::getAngle(void)
{
	return m_angle;
}

bool Part::collisionWithCircle(Coordinate p1, Coordinate p2, Coordinate pc, double radius)
{
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;

	double t = ((pc.x - p1.x)*dx + (pc.y - p1.y)*dy)/(dx*dx + dy*dy);

	double cx = dx*t + p1.x;
	double cy = dy*t + p1.y;

	double d2 = (pc.x - cx)*(pc.x - cx) + (pc.y - cy)*(pc.y - cy);

	//if the distance from the center of the ball to the arm is larger than
	//the radius of the ball, it's OK.
	if(d2 > radius * radius){
		return false;
	}
	else if(t >= 0.0 && t <= 1.0){
		return true;
	}

	//Otherwise: distance from the end points of the arm should be longer than
	//the radius.
	double end1_d2 = (pc.x - p2.x)*(pc.x - p2.x) + (pc.y - p2.y)*(pc.y - p2.y);
	double end2_d2 = (pc.x - p1.x)*(pc.x - p1.x) + (pc.y - p1.y)*(pc.y - p1.y);
	if(end1_d2 <= radius * radius || end2_d2 <= radius * radius){
		return true;
	}

	return false;
}
