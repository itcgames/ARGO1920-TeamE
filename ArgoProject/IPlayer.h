#ifndef IPLAYER
#define IPLAYER

#include "SDL.h"
#include "Entity.h"
#include "ECS.h"
#include "RenderSystem.h"
#include "BehaviourSystem.h"
#include "CommandSystem.h"
#include "Renderer.h"
#include "AnimationSystem.h"
#include "Data.h"
#include "FiniteState.h"
#include "Audio.h"
#include "CollisionSystem.h"
#include "ParticleSystem.h"
#include <iostream>

class IPlayer
{
public:
	virtual ~IPlayer() {}
	virtual void init(RenderSystem* t_rs, SDL_Rect* camera, Vector2 startPos) = 0;
	virtual void update() = 0;
	virtual void processEvents(bool isRunning) = 0;
	virtual Vector2 getPosition() = 0;
	virtual float getHealth() = 0;
	virtual int getMaxHealth() = 0;
	virtual Entity* getEntity() = 0;
	virtual void setAction() = 0;
	virtual void Attack(float&m_enemyHealth) = 0;
	virtual void setDamage(float t_dmg) = 0;
	virtual bool getSeek() = 0;
	virtual void setSeek(bool seek) = 0;
	virtual bool getMenuActive() = 0;
	virtual void turnOffMenu() = 0;

	//virtual void hit(Entity* t_enemy) = 0;

	virtual void setMove(bool move) = 0;
	virtual void setTargetPosition(Vector2 vector) = 0;

	virtual FSM* getFSM() = 0;


	virtual SDL_Rect* getRect() = 0;
	ManaComponent* m_mc;

	bool m_skillCooldown[3];
	bool m_skillActive[3];
	int m_killCount;
	float m_attackFrame;
protected:
	Entity* m_player;

	//Components
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	StatsComponent* m_statc;
	HealthComponent* m_hc;
	StaminaComponent* m_stc;
	BehaviourComponent* m_bc;
	ActiveComponent* m_ac;

	//systems
	BehaviourSystem* m_bs;
	RenderSystem* m_rs;
	InputHandler* m_ih;
	AnimationSystem* m_anim;

	//Player animated sprite
	SDL_Rect* m_positionRect;
	SDL_Rect* m_animationRect;
	SDL_Texture* m_playerTexture;
	SDL_Texture* m_collisionTexture;

	//Particles
	ParticleSystem* m_particleEffects;

	bool m_seek;

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

	Audio* walkSound;
	Audio* attackSound;
	Audio* slamAttackSound;
	Audio* spinAttackSound;
	float dmg = 0.1;
	int M_MAX_HEALTH;

	int m_attackTimer;
	bool attackFinished;
};

#endif // !IPLAYER