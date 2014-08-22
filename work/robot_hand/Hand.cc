#include "Hand.h"
using namespace std;

Hand::Hand(int base_length,int side_length) : Part()
{
	m_base_length = base_length;
	m_side_length = side_length;
}

Hand::~Hand(){}

//hand has no joint so nothing is set
void Hand::setAngle(int a){return;}

Coordinate Hand::getEndPosition(Coordinate prev_pos,int prev_angle)
{
	//Hand does not have the definition of end point.
	return prev_pos;
}

vector<Coordinate> Hand::getEndPositions(Coordinate prev_pos,int prev_angle)
{
	vector<Coordinate> ans,local_pos;

	local_pos.push_back(Coordinate{(double)m_side_length,(double)(m_base_length/2)});
	local_pos.push_back(Coordinate{0.0,(double)(m_base_length/2)});
	local_pos.push_back(Coordinate{0.0,(double)(-m_base_length/2)});
	local_pos.push_back(Coordinate{(double)m_side_length,(double)(-m_base_length/2)});

	double c = cos(prev_angle*3.141592/180.0);	
	double s = sin(prev_angle*3.141592/180.0);	

	for(auto p : local_pos){
		double x = prev_pos.x + p.x*c - p.y*s;
		double y = prev_pos.y + p.x*s + p.y*c;

		ans.push_back(Coordinate{x,y});
	}

	return ans;
}

int Hand::getStateNum(void)
{
	return 1;
}

bool Hand::isInside(double relative_x, double relative_y)
{
	if(relative_x <= 0.0)
		return false;

	if(relative_x > m_side_length)
		return false;
	
	if(fabs(relative_y) > m_base_length/2)
		return false;

	return true;
}

bool Hand::collisionWithTarget(Coordinate prev_pos,int prev_angle,Target *target)
{
	vector<Coordinate> end_poss = getEndPositions(prev_pos,prev_angle);
	for(unsigned int i=0;i<end_poss.size()-1;i++){
		Coordinate pos_a = end_poss[i];
		Coordinate pos_b = end_poss[i+1];

		//cerr << pos_a.x << " " << pos_b.x << " " << target->radius << endl;
		if(collisionWithCircle(pos_a,pos_b,
			Coordinate{(double)target->x,(double)target->y},target->radius)){
			return true;
		}
	}
	return false;
}

void Hand::draw(int size,Pixel *img[],double mag,int cx,int cy,Coordinate &pos,double ang)
{
	vector<Coordinate> end_poss = getEndPositions(pos,ang);

	for(unsigned int i=0;i<end_poss.size()-1;i++){
		Coordinate pos_a = end_poss[i];
		Coordinate pos_b = end_poss[i+1];

		double start_x = (double)cx + pos_a.x*mag;
		double start_y = (double)cy + pos_a.y*mag;
		double end_x = (double)cx + pos_b.x*mag;
		double end_y = (double)cy + pos_b.y*mag;
	
		for(int i=0;i<=size;i++){
			int x = int(start_x + (end_x - start_x)*(1.0 - ((double)i)/size));
			int y = int(start_y + (end_y - start_y)*(1.0 - ((double)i)/size));
	
			if(x < 0 || x >= size)
				continue;
			if(y < 0 || y >= size)
				continue;
	
			img[x][y] = {0,0,0};
		}

	}
}
