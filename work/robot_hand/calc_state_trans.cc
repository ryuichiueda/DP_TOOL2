#include <iostream>
#include <vector>
#include "System.h"
#include "Arm.h"
#include "Hand.h"
using namespace std;

int main(int argc, char const* argv[])
{
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	Target ball{x,y,5};

	//definition of sys
	/*
	Arm arm0("arm0",100,0,180);
	Arm arm1("arm1",100,-160,160);
	Hand hand(30,30);
*/

	System sys(&ball);
/*
	sys.setPart(&arm0);
	sys.setPart(&arm1);
	sys.setPart(&hand);
*/

	sys.writeHeader();
	sys.writeStateTransition();
	sys.writeFinalStates();
}
