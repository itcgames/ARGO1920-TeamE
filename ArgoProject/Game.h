

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <time.h>


#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
//#include "CreditsState.h"
//#include "EndState.h"
//#include "OptionsState.h"
//#include "CharacterSelectState.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "Data.h"
#include "LevelLoader.h"

class Game
{
public:
	Game(GameData& t_data);
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void update();

	void processEvents();
	void render();
	void cleanUp();

	bool running() { return isRunning; }


private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* m_ecsTexture;
	GameData m_data;

	bool m_exitGame; // control exiting game

	// InputHandler Variables
	bool exit;
	//InputHandler* inputHandler;

	////Creates the Command Queue
	//std::vector<Command*> commandQueue;


	GameStateMachine* m_gameStateMachine;
	int timer = 0;

	//
	Entity* m_entity;
	//
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	//
	RenderSystem* m_rs;
	//
	SDL_Rect* m_playerRect;

	static const int M_MAX_STAT_PRESETS = 2;
};

#endif // !GAME_H