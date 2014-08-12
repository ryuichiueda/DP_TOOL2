#include <iostream>
#include <vector>
#include "Robot.h"
#include "Arm.h"
#include "Hand.h"
using namespace std;

class Ball{
public: 
	Ball()
	{
		m_x = 50.0;
		m_y = 100.0;
		m_radius = 5.0;
	}
	double m_x,m_y,m_radius;
};

int main(int argc, char const* argv[])
{
	//definition of robot
	Arm arm0("arm0",100.0,-90.0,90.0,1.0);
	Arm arm1("arm1",100.0,-160.0,160.0,1.0);
	Hand hand(30.0,30.0);

	Robot robot;
	robot.setPart(&arm0);
	robot.setPart(&arm1);
	robot.setPart(&hand);

/*
	robot.getPart(0)->setAngle(30.0);
	robot.getPart(1)->setAngle(-60.0);

	Coordinate c = robot.getEndPosition();
	cout << c.x << " " << c.y << " " << robot.getEndAngle() << endl;
*/

	//definition of ball to be gripped
	Ball ball;

	cout << ball.m_x << endl;

//	arm1.stateToAngleDeg(10000);

	exit(0);
}
