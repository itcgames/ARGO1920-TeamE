#pragma once
#include "GameState.h"
#include "TextureManager.h"
#include "SDL.h"
#include <iostream>

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter(SDL_Renderer* t_renderer);
	virtual bool onExit();

	virtual std::string getStateID() const { return m_menuID; };

private:
	//Animation VAR
	int m_currentFrame;

	static const std::string  m_menuID;

	SDL_Renderer* menuRender;
};

