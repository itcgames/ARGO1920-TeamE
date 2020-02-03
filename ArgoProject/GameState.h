#pragma once
#include <string>
#include "SDL.h"

class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter(SDL_Renderer* t_renderer) = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;
};