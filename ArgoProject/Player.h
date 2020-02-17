
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
	bool getSeek();

	void setSeek(bool seek);

	SDL_Rect* getRect() { return m_playerRect; }

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

	bool m_seek;

	int spriteSheetY = 0;

};

