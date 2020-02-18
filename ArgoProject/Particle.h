#pragma once
#include "GameState.h"
#include "SDL.h"
#include "Vector2.h"
#include <iostream>

class Particle
{
public:
	Particle(const std::string& currentState,int maxAliveTime, Vector2 pos);
	~Particle();

	void CreateParticle();

	void update();
	void render();

	bool Alive();

private:
	std::string m_currentState;
	bool m_alive = false;
	int m_timeAlive = 0;
	int MAX_PARTICLE_LIFE;

	//Properties
	Vector2 m_pos;
	int m_speed = 5;
	Vector2 m_direction;
	SDL_Color myCol;
	int size = 15;

	//Rectangle
	SDL_Rect m_particle;

	//Surface
	SDL_Texture *m_texture;
	int textureWidth, textureHeight;


};

