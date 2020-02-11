#pragma once
#include "GameState.h"
#include "SDL.h"
#include <vector>
#include <iostream>
#include "LevelLoader.h"
class GameStateMachine
{
public:
	void pushState(GameState* t_state);
	void changeState(GameState* t_state);
	void popState();

	void update();
	void render();
	void processEvents(bool &isRunning);
	std::vector<GameState*>& getGameStates() { return m_gameStateSystem; }


private:
	GameData m_data;
	std::vector<GameState*> m_gameStateSystem;
};

