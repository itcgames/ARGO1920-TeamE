#ifndef LOADSTATE
#define LOADSTATE
#include "GameState.h"
#include "PlayState.h"
#include <iostream>

class LoadState : public GameState
{
public:
	LoadState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_loadID; };

private:
	Vector2 m_cameraDimensions;
	GameStateMachine* m_stateMachine;
	static const std::string  m_loadID;

	std::string Loading[2];

	TTF_Font* Abel;

	Text* m_text[2];


	int m_timerCount = 120;
};

#endif

