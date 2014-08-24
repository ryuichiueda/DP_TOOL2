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

	for(int bx=140;bx<=149;bx++){
		cerr << bx << endl;
		for(int by=140;by<=149;by++){
			if(! sys.readValues(bx,by)){
				die("Value Format Error");
			}
		}
	}

	sys.getPart(0)->setAngle(170);
	sys.getPart(1)->setAngle(80);
	if(! sys.doPfcMotion()){
		die("not in final state");
		exit(1);
	}
}
