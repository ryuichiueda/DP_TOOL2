#include "Robot.h"
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
