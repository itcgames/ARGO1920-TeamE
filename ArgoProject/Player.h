
#include "SDL.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "StatsComponent.h"
#include "RenderSystem.h"
#include "BehaviourComponent.h"
#include "BehaviourSystem.h"
#include "CommandSystem.h"
#include "Renderer.h"
#include "Data.h"
#include "FiniteState.h"
#include <iostream>

class Player
{
public:
	void init(RenderSystem* t_rs, SDL_Rect* camera, Vector2 startPos);
	void update();
	void animate();
	void processEvents(bool isRunning);
	Vector2 getPosition() { return m_pc->getPosition(); }
	Entity* getEntity() { return m_player; };

	Entity* m_player;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	StatsComponent* m_statc;
	BehaviourComponent* m_bc;
	BehaviourSystem* m_bs;
	RenderSystem* m_rs;
	InputHandler* m_ih;

	SDL_Rect* m_playerRect;
	SDL_Texture* m_playerTexture;
	SDL_Rect* playerPos;

	SDL_Rect* m_camera;

	FSM* finiteStateMachine;
	FiniteState* state;

	//Creates the Command Queue
	std::vector<Command*> commandQueue;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
};

