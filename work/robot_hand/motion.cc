#include <iostream>
#include <vector>
#include "System.h"
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

	//definition of sys
	Arm arm0("arm0",100,0,180);
	Arm arm1("arm1",100,-160,160);
	Hand hand(30,30);

	System sys(&ball);
	sys.setPart(&arm0);
	sys.setPart(&arm1);
	sys.setPart(&hand);

	if(! sys.readPolicy()){
		die("Policy Format Error");
	}

	sys.getPart(0)->setAngle(70);
	sys.getPart(1)->setAngle(0);
	if(! sys.doMotion()){
		die("not in final state");
		exit(1);
	}
}
