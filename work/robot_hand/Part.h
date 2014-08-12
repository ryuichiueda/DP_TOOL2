#ifndef _PART_H__
#define _PART_H__

#include "Coordinate.h"

class Part{
protected:
	double m_angle;
public:
	Part();
	virtual ~Part();
	virtual Coordinate getEndPosition(Coordinate prev_pos,double prev_angle) = 0;
	virtual bool setAngle(double a) = 0;
	virtual double getAngle(void);
};

#endif
