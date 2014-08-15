#ifndef _PART_H__
#define _PART_H__

#include <vector>
using namespace std;

struct Coordinate;

class Part{
protected:
	int m_angle;
	vector<double> m_discrete_states;
public:
	Part();
	virtual ~Part();
	virtual Coordinate getEndPosition(Coordinate prev_pos,int prev_angle) = 0;
	virtual void setAngle(int a) = 0;
	virtual int getStateNum(void) = 0;
	virtual int getAngle(void);

	virtual bool collisionWithBall(Coordinate prev_pos,int prev_angle,
					double x,double y,double r) = 0;

	bool isFinalState(int index,int x, int y, int r);
};

#endif
