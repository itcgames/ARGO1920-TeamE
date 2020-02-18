#ifndef PLAYER
#define PLAYER

#include "SDL.h"
#include "Entity.h"
#include "ECS.h"
#include "RenderSystem.h"
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
	void setAction();


	void hit(Entity* t_enemy);


	SDL_Rect* getRect() { return m_positionRect; }

private:


	Entity* m_player;

	PositionComponent* m_pc;
	SpriteComponent* m_sc;

	StatsComponent* m_statc;
	HealthComponent* m_hc;
	ManaComponent* m_mc;
	StaminaComponent* m_stc;

	BehaviourComponent* m_bc;
	ActiveComponent* m_ac;


	BehaviourSystem* m_bs;
	RenderSystem* m_rs;

	InputHandler* m_ih;



	//Player animated sprite
	SDL_Rect* m_positionRect;
	SDL_Rect* m_animationRect;
	SDL_Texture* m_playerTexture;
	SDL_Texture* m_collisionTexture;


	SDL_Rect* m_camera;

	FSM* finiteStateMachine;
	FiniteState* state;

	//Creates the Command Queue
	std::vector<Command*> commandQueue;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
	int colTextureWidth, colTextureHeight;
	int spriteSheetY = 0;
	int spriteSheetX = 0;
};

#endif