#pragma once
#include "GameState.h"
#include "MenuState.h"
#include <string>
class HighScoreState :
	public GameState
{
public:
	HighScoreState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_highScoreID; };

private:
	Vector2 m_cameraDimensions;

	static const std::string  m_highScoreID;

	std::string m_names[10];

	SDL_Rect* m_nameRects[10];
	SDL_Texture* m_nameTextures[10];

	SDL_Rect* m_slotRect[10];
	SDL_Texture* m_slotTexture;

	TTF_Font* Sans;

	GameStateMachine* m_stateMachine;
};

