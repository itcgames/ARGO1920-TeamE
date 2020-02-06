#pragma once
#include "SDL.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "BehaviourComponent.h"
#include "BehaviourSystem.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include <iostream>

class Ai
{
public:
	void initialize(RenderSystem* t_rs);
	void update(Vector2 t_position);
	void render();
	void destroy() { delete this; }
private:
	Entity* m_enemy;
	SDL_Rect* m_rect;
	SDL_Texture* m_texture;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	BehaviourComponent* m_bc;
	BehaviourSystem* m_bs;

};

