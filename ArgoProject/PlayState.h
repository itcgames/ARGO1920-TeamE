#pragma once

#include "GameState.h"
#include "SDL.h"
#include "Renderer.h"
#include "Player.h"
#include <iostream>
#include "Ai.h"
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

<<<<<<< HEAD
	//
	Entity* m_player;
	Entity* m_mouse;
	//
	PositionComponent* m_pc;
	SpriteComponent* m_sc;

	//Enemy
	Ai m_enemy;

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

	bool move = false;

	int maxSpeed = 4;

	Vector2 mousePosition = Vector2(100, 100);

	Vector2 m_playerVelocity = Vector2(0, 0);

	Vector2 Normalize(Vector2& t_vector);

=======
	RenderSystem* m_rs;
	Player m_player;
>>>>>>> 5d08310d226791b074561675216462481b0f601d
};

