//#pragma once
#ifndef HOSTSEARCHSTATE
#define HOSTSEARCHSTATE

#include "GameState.h"
#include "PlayState.h"
#include "Data.h"
class HostSearchState :
	public GameState
{
public:
	HostSearchState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_hostSearchID; };

private:
	static const std::string  m_hostSearchID;

	Vector2 m_cameraDimensions;

	SDL_Rect* m_hostRect;
	SDL_Texture* m_hostTexture;

	SDL_Rect* m_searchRect;
	SDL_Texture* m_searchTexture;

	SDL_Rect* m_exitRect;
	SDL_Texture* m_exitTexture;

	GameStateMachine* m_stateMachine;

	TTF_Font* Abel;

	Text* m_text[3];
};

#endif