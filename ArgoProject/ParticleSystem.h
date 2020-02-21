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
	BLOOD,
	BARSEFFECT
};

class ParticleSystem
{
public:
	ParticleSystem(const std::string& currentState, RenderSystem* t_rs);
	~ParticleSystem();

	void update();
	void render();

	void AddParticles(Vector2 pos,Type typeID, int numofParticles);

	Vector2 disperseInCircle(int circleRadius);

	Vector2 disperseInRect(Vector2 pos, int width, int height);

	//Utility
	double GenerateRandomNumber(double min,double max);

private:
	std::vector<std::unique_ptr<Particle>> m_particles;

	std::string m_currentState;

	RenderSystem* m_rs;


};
 