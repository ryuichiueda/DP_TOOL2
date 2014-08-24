#ifndef _PF_H__
#define _PF_H__

#include<vector>
using namespace std;

class ParticleFilter{
private:
	struct Particle{int x, y;double w;};
	int m_particle_num;
public:
	ParticleFilter();
	~ParticleFilter();
	vector<Particle> m_particles;

	void print(void);

};

#endif
