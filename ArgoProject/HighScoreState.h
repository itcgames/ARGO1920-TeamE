#ifndef HIGHSCORESTATE
#define HIGHSCORESTATE
//#pragma once
#include "GameState.h"
#include "MenuState.h"
#include "LevelLoader.h"
#include <string>
#include "Data.h"

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
	void writeScores();
	void newScore(int t_newScore, std::string t_newName);
	virtual std::string getStateID() const { return m_highScoreID; };

private:
	Vector2 m_cameraDimensions;

	static const std::string  m_highScoreID;
	int m_score[10];
	std::string m_names[10];
	std::string m_scoreString[10];
	std::string m_display[10];

	SDL_Rect* m_slotRect[10];
	SDL_Texture* m_slotTexture;

	TTF_Font* Abel;

	Text* m_text[10];

	GameStateMachine* m_stateMachine;

	SDL_Rect* m_exitOption;
	SDL_Texture* m_exitOptionTexture;

	SDL_Rect* m_background;
	SDL_Texture* m_backgroundTexture;
};

#endif