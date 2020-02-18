#pragma once
#include "GameState.h"
#include "SDL.h"
#include "Vector2.h"
#include <iostream>
#include "Particle.h"

#define MAX_PARTICLES  1000

class ParticleSystem
{
public:
	ParticleSystem(const std::string& currentState);
	~ParticleSystem();

	void update();
	void render();

	std::vector<std::unique_ptr<Particle>> m_particles;

	std::string m_currentState;

};
 