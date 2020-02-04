

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "Renderer.h"

class Game
{
public:
	Game();
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
};

#endif // !GAME_H