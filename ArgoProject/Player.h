
#include "SDL.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "BehaviourComponent.h"
#include "BehaviourSystem.h"
#include "Renderer.h"
#include <iostream>

class Player
{
public:
	void init(RenderSystem* t_rs, SDL_Rect* camera, Vector2 startPos);
	void update();
	void processEvents(bool isRunning);
	Vector2 getPosition() { return m_pc->getPosition(); }
	Entity* getEntity() { return m_player; };

	Entity* m_player;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	BehaviourComponent* m_bc;
	BehaviourSystem* m_bs;
	RenderSystem* m_rs;

	SDL_Rect* m_playerRect;
	SDL_Texture* texture;
	SDL_Rect* m_camera;

	bool move = false;

	int maxSpeed = 4;

	Vector2 mousePosition = Vector2(0, 0);

	Vector2 m_velocity = Vector2(0, 0);
};

