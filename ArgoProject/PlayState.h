#pragma once

#include "GameState.h"
#include "SDL.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "Renderer.h"
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

	Vector2 GetPosition();
	virtual SDL_Rect* GetViewRect();

private:
	static const std::string  m_playID;

	//
	Entity* m_player;
	Entity* m_mouse;
	//
	PositionComponent* m_pc;
	SpriteComponent* m_sc;

	PositionComponent* m_mousepc;
	SpriteComponent* m_mousesc;
	//
	RenderSystem* m_rs;

	RenderSystem* m_mousers;
	//
	SDL_Rect* m_playerRect;
	SDL_Texture* texture;
	SDL_Rect* m_mouseRect;
	SDL_Texture* mouseTexture;
	SDL_Rect* m_viewRect;

	bool move = false;

	int maxSpeed = 4;

	Vector2 mousePosition = Vector2(100, 100);

	Vector2 m_velocity = Vector2(0, 0);

	Vector2 Normalize(Vector2& t_vector);

};

