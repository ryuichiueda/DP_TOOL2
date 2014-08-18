#include <iostream>
#include <vector>
#include "System.h"
#include "Arm.h"
#include "Hand.h"
using namespace std;

int main(int argc, char const* argv[])
{
	//definition of ball to be gripped
	//Target ball{50.0,100.0,5.0};

	//definition of sys
	/*
	Arm arm0("arm0",100,0,180);
	Arm arm1("arm1",100,-160,160);
	Hand hand(30,30);
*/

	System sys;
/*
	sys.setPart(&arm0);
	sys.setPart(&arm1);
	sys.setPart(&hand);
*/

	sys.writeHeader();
	sys.writeStateTransition();
	sys.writeFinalStates();
}
