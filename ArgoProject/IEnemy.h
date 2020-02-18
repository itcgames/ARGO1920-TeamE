#ifndef IENEMY
#define IENEMY
#include <iostream>
#include "Vector2.h"
#include "SDL.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "BehaviourComponent.h"
#include "StatsComponent.h"
#include "BehaviourSystem.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include <iostream>
#include "Data.h"

class IEnemy
{
public:
	virtual ~IEnemy()  {}
	virtual void initialize(RenderSystem* t_rs, Vector2 t_Position, std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount) = 0;
	virtual void update(Vector2 t_position) = 0;;
	virtual void destroy() = 0;
	virtual Entity* getEntity() = 0;

	virtual int getAttackTime() = 0;
	virtual void setAttackTime(int attackTime) = 0;
protected:
	Entity* m_enemy;
	SDL_Rect* m_rect;
	SDL_Texture* m_texture;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	BehaviourComponent* m_bc;
	BehaviourSystem* m_bs;
	StatsComponent* m_statsC;
	HealthComponent* m_hc;
	ActiveComponent* m_ac;

	Vector2 m_normalizedVec;

	int m_attackTime;
};

#endif // !IENEMY