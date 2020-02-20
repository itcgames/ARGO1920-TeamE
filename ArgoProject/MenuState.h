#ifndef MENUSTATE
#define MENUSTATE
#include "GameState.h"
//#include "PlayState.h"
#include "Data.h"
#include "HighScoreState.h"
#include "CharacterSelectState.h"
#include "OptionsState.h"
#include "SDL.h"
#include "CreditsState.h"
#include "HostSearchState.h"
#include <iostream>

class MenuState : public GameState
{
public:
	MenuState(Vector2& t_dimensions, GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_menuID; };

private:
	//Animation VAR
	int m_currentFrame;

	static const std::string  m_menuID;

	Vector2 m_buttonDimensions;

	SDL_Rect* m_singlePlayerButton;
	SDL_Texture* m_singlePlayerButtonTexture;

	SDL_Rect* m_multiPlayerButton;
	SDL_Texture* m_multiPlayerButtonTexture;

	SDL_Rect* m_optionsButton;
	SDL_Texture* m_optionsButtonTexture;

	SDL_Rect* m_creditsButton;
	SDL_Texture* m_creditsButtonTexture;

	SDL_Rect* m_exitButton;
	SDL_Texture* m_exitButtonTexture;

	TTF_Font* Abel;

	Text* m_text[5];

	GameStateMachine* m_stateMachine;
};

#endif