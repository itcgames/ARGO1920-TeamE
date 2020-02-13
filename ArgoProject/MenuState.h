#pragma once
#include "GameState.h"
#include "PlayState.h"
#include "SDL.h"
#include "Renderer.h"
#include "Vector2.h"
#include "GameStateMachine.h"
#include <iostream>
#include <vector>

class MenuState : public GameState
{
public:
	MenuState(Vector2 &t_dimensions, GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool &isRunning);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_menuID; };

private:
	//Animation VAR
	int m_currentFrame;

	static const std::string  m_menuID;

	Vector2 m_buttonDimensions;

	SDL_Rect* m_playButton;
	SDL_Texture* m_playButtonTexture;

	SDL_Rect* m_exitButton;
	SDL_Texture* m_exitButtonTexture;

	GameStateMachine* m_stateMachine;
};

