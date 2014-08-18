#ifndef _PART_H__
#define _PART_H__

#include <vector>
using namespace std;

struct Coordinate;
struct Pixel;
struct Target;

class Part{
protected:
	int m_angle;
	int m_discrete_state;
	vector<double> m_discrete_states;

	virtual bool collisionWithCircle(Coordinate p1, Coordinate p2, Coordinate pc, double radius);
public:
	Part();
	virtual ~Part();
	virtual Coordinate getEndPosition(Coordinate prev_pos,int prev_angle) = 0;
	virtual void setAngle(int a) = 0;
	virtual int getAngle(void);
	virtual int getStateNum(void) = 0;

	virtual void draw(int size,Pixel *img[],double mag,int cx,int cy,Coordinate &pos,double ang) = 0;

	int getState(void){return m_discrete_state;}

	virtual bool collisionWithTarget(Coordinate prev_pos,int prev_angle,Target *target) = 0;

	bool isFinalState(int index,int x, int y, int r);
};

#endif
