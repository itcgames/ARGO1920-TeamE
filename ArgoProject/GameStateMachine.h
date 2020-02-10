#pragma once
#include "GameState.h"
#include "SDL.h"
#include <vector>
#include <iostream>
class GameStateMachine
{
public:
	void pushState(GameState* t_state);
	void changeState(GameState* t_state);
	void popState();

	void update();
	void render();
	void processEvents(bool isRunning);
	std::vector<GameState*>& getGameStates() { return m_gameStateSystem; }


private:
	std::vector<GameState*> m_gameStateSystem;
};

