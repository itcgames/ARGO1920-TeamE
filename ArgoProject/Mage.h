#ifndef MAGE
#define MAGE

#include "IPlayer.h"

class Mage : public IPlayer
{
public:
	Mage();
	virtual ~Mage();
	void init(RenderSystem* t_rs, SDL_Rect* t_camera, Vector2 startPos);
	void update();
	void animate();
	void processEvents(bool isRunning);
	Vector2 getPosition() { return m_pc->getPosition(); }
	Entity* getEntity() { return m_player; }
	void setAction();
	//void hit(Entity* t_enemy);
	SDL_Rect* getRect() { return m_positionRect; }
	void Attack(float& m_enemyHealth);
	void setDamage(float t_dmg) { dmg = t_dmg; }
};

#endif // !MAGE