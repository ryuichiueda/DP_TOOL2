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

int main(int argc, char const* argv[])
{
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	Target ball{x,y,5};

	System sys(&ball);

	for(int bx=120;bx<=130;bx++){
		cerr << bx << endl;
		for(int by=100;by<=120;by++){
			if(! sys.readValues(bx,by)){
				die("Value Format Error");
			}
		}
	}
	return 0;

	sys.getPart(0)->setAngle(170);
	sys.getPart(1)->setAngle(80);
	if(! sys.doPfcMotion()){
		die("not in final state");
		exit(1);
	}
}
