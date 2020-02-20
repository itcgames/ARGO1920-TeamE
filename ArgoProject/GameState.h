#ifndef GAMESTATE
#define GAMESTATE
#include <string>
#include "Renderer.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include "LevelLoader.h"
#include "GameStateMachine.h"
#include "Vector2.h"
#include <iostream>
#include "Text.h"
class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void processEvents(bool &isRunning) = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;
};

#endif