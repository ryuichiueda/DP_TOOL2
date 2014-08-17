#include <iostream>
#include <vector>
#include "Robot.h"
#include "Arm.h"
#include "Hand.h"
using namespace std;

void die(string reason){
	cerr << "value_iteration: [ERROR] " << reason << endl;
	exit(1);
}

/*
class Target{
public: 
	Target()
	{
		m_x = 50.0;
		m_y = 100.0;
		m_radius = 5.0;
	}
	double m_x,m_y,m_radius;
};
*/

int main(int argc, char const* argv[])
{
	//definition of ball to be gripped
	Target ball{50.0,100.0,5.0};

	//definition of robot
	Arm arm0("arm0",100,0,180);
	Arm arm1("arm1",100,-160,160);
	Hand hand(30,30);

	Robot robot(&ball);
	robot.setPart(&arm0);
	robot.setPart(&arm1);
	robot.setPart(&hand);

	if(! robot.readPolicy()){
		die("Policy Format Error");
	}

	robot.getPart(0)->setAngle(70);
	robot.getPart(1)->setAngle(0);
	if(! robot.doMotion()){
		die("not in final state");
		exit(1);
	}
}
