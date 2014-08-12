#include <iostream>
#include <vector>
#include "Robot.h"
using namespace std;

int main(int argc, char const* argv[])
{
/*
	int obj_x = 50;
	int obj_y = 100;
*/

	//definition of robot
	Arm arm1(100.0,-90.0,90.0);
	Arm arm2(100.0,-160.0,160.0);
	Hand hand(30.0,30.0);

	Robot robot;
	robot.setPart(&arm1);
	robot.setPart(&arm2);
	robot.setPart(&hand);

	robot.getPart(0)->setAngle(30.0);
	robot.getPart(1)->setAngle(-60.0);

	Coordinate c = robot.getEndPosition();
	cout << c.x << " " << c.y << " " << robot.getEndAngle() << endl;

	exit(0);
}
