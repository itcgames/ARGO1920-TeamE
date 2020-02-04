#pragma once

#include "GameState.h"
#include "TextureManager.h"
#include "SDL.h"

#include <iostream>

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_playID; };

private:
	static const std::string  m_playID;
};

