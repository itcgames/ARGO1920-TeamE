#ifndef HUD_H
#define HUD_H

#include "SDL.h"
#include "Vector2.h"
#include "Renderer.h"
#include <iostream>
#include "FSM.h"
class HUD
{
public:
	HUD(Vector2 t_cameraDimension, float t_originalHealth);
	~HUD();

	void update(float t_currentHealth);
	void render();

	SDL_Rect m_viewableArea;

	SDL_Rect m_background;

	SDL_Rect m_health;
	SDL_Rect m_healthOverflow;

	SDL_Rect m_mana;
	SDL_Rect m_manaOverflow;

	SDL_Texture* m_texture;
	SDL_Texture* m_healthTexture;
	SDL_Texture* m_healthOverflowTexture;
	SDL_Texture* m_manatexture;

	bool q = false;
	bool w = false;
	bool e = false;

	float healthFullWidth;
	float originalHealth;

	float manaFullWidth;
};

#endif