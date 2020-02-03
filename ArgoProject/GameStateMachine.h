#pragma once
#include "GameState.h"
#include "SDL.h"
#include <vector>
#include <iostream>
class GameStateMachine
{
public:
	void pushState(GameState* t_state, SDL_Renderer* t_renderer);
	void changeState(GameState* t_state,SDL_Renderer* t_renderer);
	void popState();

	void update();
	void render();

	std::vector<GameState*>& getGameStates() { return m_gameStateSystem; }


private:
	std::vector<GameState*> m_gameStateSystem;
};

