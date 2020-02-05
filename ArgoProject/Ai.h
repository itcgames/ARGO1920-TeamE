#pragma once
#include "SDL.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include <iostream>

class Ai
{
public:
	void initialize(RenderSystem* t_rs);
	void update();
	void render();
private:
	Entity* m_enemy;
	SDL_Rect* m_enemyRect;
	SDL_Texture* m_enemyTexture;
	PositionComponent* m_enemyPc;
	SpriteComponent* m_enemySc;

};

