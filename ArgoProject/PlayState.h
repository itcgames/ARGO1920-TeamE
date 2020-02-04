#pragma once

#include "GameState.h"
#include "TextureManager.h"
#include "SDL.h"

#include <iostream>

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter(SDL_Renderer* t_renderer);
	virtual bool onExit();

	virtual std::string getStateID() const { return m_playID; };

private:
	static const std::string  m_playID;

	SDL_Renderer* playRender = nullptr;
};

