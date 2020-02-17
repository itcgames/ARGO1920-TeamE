#pragma once
#include "SDL.h"
#include "Renderer.h"
#include <iostream>
#include "FSM.h"
class HUD
{
public:
	HUD();
	~HUD();

	void update();
	void render();

	SDL_Rect m_viewableArea;

	SDL_Rect m_background;
	SDL_Rect m_health;
	SDL_Rect m_mana;

	SDL_Texture* m_texture;
	SDL_Texture* m_healthtexture;
	SDL_Texture* m_manatexture;

	bool q = false;
	bool w = false;
	bool e = false;
};

