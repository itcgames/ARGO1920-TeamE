#pragma once
#include "SDL.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "BehaviourComponent.h"
#include "StatsComponent.h"
#include "BehaviourSystem.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include <iostream>
#include "Data.h"

class Ai
{
public:
	void initialize(RenderSystem* t_rs, Vector2 t_Position, std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount);
	void update(Vector2 t_position);
	void render();
	void destroy() { delete this; }
	Entity* getEntity() { return m_enemy; };

private:
	Entity* m_enemy;
	SDL_Rect* m_rect;
	SDL_Texture* m_texture;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	BehaviourComponent* m_bc;
	BehaviourSystem* m_bs;
	StatsComponent* m_statsC;

};

