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
	virtual bool getSeek() { return m_seek; }
	virtual bool getMenuActive();
	virtual void turnOffMenu();
	virtual void setSeek(bool seek) { m_seek = seek; }
	//void hit(Entity* t_enemy);
	SDL_Rect* getRect() { return m_positionRect; }

	void setMove(bool move) { m_ih->move = move; }
	void setTargetPosition(Vector2 vector) { m_ih->mousePosition = vector; }

	void Attack(float& m_enemyHealth);
	void setDamage(float t_dmg) { dmg = t_dmg; }

	//bool m_skillCooldown[3];
};

#endif // !MAGE