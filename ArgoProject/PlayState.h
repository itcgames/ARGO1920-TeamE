#pragma once

#include "GameState.h"
#include "SDL.h"
#include "Renderer.h"
#include "Player.h"
#include "Ai.h"
#include "CollisionSystem.h"
#include <iostream>

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual void processEvents(bool isRunning);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_playID; };

private:
	static const std::string m_playID;

	RenderSystem* m_rs;
	CollisionSystem* m_cs;
	Player m_player;
	Ai* m_enemy = new Ai;
};

