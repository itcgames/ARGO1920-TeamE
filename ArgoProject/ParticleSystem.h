#pragma once
#include "GameState.h"
#include "SDL.h"
#include "Vector2.h"
#include <iostream>
#include "Particle.h"
#include <random>

#define MAX_PARTICLES  1000

enum class Type
{
	EXPLOSION,
	TRAIL,
	BLOOD
};

class ParticleSystem
{
public:
	ParticleSystem(const std::string& currentState, int numofParticles, Type typeID);
	~ParticleSystem();

	void update();
	void render();

	void ChooseType(Type typeID, int numofParticles);

	Vector2 disperseInCircle();

	//Utility
	double GenerateRandomNumber(double min,double max);

private:
	std::vector<std::unique_ptr<Particle>> m_particles;

	std::string m_currentState;


};
 