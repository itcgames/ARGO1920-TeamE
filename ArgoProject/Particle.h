#pragma once
#include "GameState.h"
#include "SDL.h"
#include "Vector2.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include <iostream>

class Particle
{
public:
	Particle(const std::string& currentState,int maxAliveTime, Vector2 pos, Vector2 t_velocity, RenderSystem* t_rs);
	~Particle();

	void CreateParticle();

	void update();
	void render();

	bool Alive();
	void setPosition(Vector2 newPos);
	void setAngle(float t_angle);
	void moveParticle(Vector2 newPos);

	Vector2 getPosition();
	float getAngle();

	Entity* getEntity() { return m_particle; };


private:
	std::string m_currentState;
	bool m_alive = false;
	int m_timeAlive = 0;
	int MAX_PARTICLE_LIFE;

	//Properties
	SDL_Point m_orgPos;
	Vector2 m_pos;
	float m_angle;
	int m_speed = 2;
	Vector2 m_direction;
	int size = 10;

	//Rectangle
	SDL_Rect* m_particleRect;

	Entity* m_particle;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	ActiveComponent* m_ac;

	//Surface
	SDL_Texture *m_texture;
	int textureWidth, textureHeight;


};

