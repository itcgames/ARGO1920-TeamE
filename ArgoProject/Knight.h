#ifndef KNIGHT
#define KNIGHT

#include "IPlayer.h"

class Knight : public IPlayer
{
public:
	Knight();
	virtual ~Knight();
	void init(RenderSystem* t_rs, SDL_Rect* t_camera, Vector2 startPos);
	void update();
	void processEvents(bool isRunning);
	Vector2 getPosition() { return m_pc->getPosition(); }
	float getHealth() { return m_hc->getHealth();  }
	Entity* getEntity() { return m_player; }
	void setAction();
	virtual bool getSeek() { return m_seek; }
	virtual void setSeek(bool seek) { m_seek = seek; }
	//void hit(Entity* t_enemy);
	SDL_Rect* getRect() { return m_positionRect; }

	void setMove(bool move) { m_ih->move = move; }
	void setTargetPosition(Vector2 vector) { m_ih->mousePosition = vector; }

	void Attack(float& m_enemyHealth);
	void setDamage(float t_dmg) { dmg = t_dmg; }

	int timer = 0;
};

#endif // !KNIGHT