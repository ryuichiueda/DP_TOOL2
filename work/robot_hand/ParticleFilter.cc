#include <iostream>
#include "ParticleFilter.h"
using namespace std;

ParticleFilter::ParticleFilter()
{
	for(int x=0;x<=149;x++){
		for(int y=0;y<=149;y++){
			m_particles.push_back(Particle{x,y,1.0});
		}
	}
	m_particle_num = m_particles.size();
}

ParticleFilter::~ParticleFilter(){}

void ParticleFilter::print(void)
{
	for(auto &i : m_particles){
		cout << "PARTICLE " << i.x << " " << i.y << " " << i.w << endl;
	}
}
