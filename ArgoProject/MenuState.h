#pragma once
#include "GameState.h"
#include "SDL.h"
#include <iostream>

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_menuID; };

private:
	//Animation VAR
	int m_currentFrame;

	static const std::string  m_menuID;

};

