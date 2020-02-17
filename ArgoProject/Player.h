
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

	//Entities
	Entity* m_player;
	Entity* m_collisionSquare;

	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	StatsComponent* m_statc;
	BehaviourComponent* m_bc;
	ActiveComponent* m_ac;
	BehaviourSystem* m_bs;
	RenderSystem* m_rs;
	InputHandler* m_ih;

	//Collision Square Components
	SpriteComponent* m_collision_sc;
	PositionComponent* m_collision_pc;
	BehaviourComponent* m_collision_bc;


	//Player animated sprite
	SDL_Rect* m_positionRect;
	SDL_Rect* m_animationRect;
	SDL_Texture* m_playerTexture;
	SDL_Texture* m_collisionTexture;

	//Player collsion Square
	SDL_Rect* m_collisionRect;

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

