#ifndef WARRIOR
#define WARRIOR

#include "IPlayer.h"

class Warrior : public IPlayer
{
public:
	Warrior();
	virtual ~Warrior();
	void init(RenderSystem* t_rs, SDL_Rect* t_camera, Vector2 startPos);
	void update();
	void animate();
	void processEvents(bool isRunning);
	Vector2 getPosition(){ return m_pc->getPosition(); }
	Entity* getEntity() { return m_player; }
	void setAction();
	virtual bool getSeek() { return m_seek; }
	virtual void setSeek(bool seek) { m_seek = seek; }
	//void hit(Entity* t_enemy);
	SDL_Rect* getRect(){ return m_positionRect; }
	void Attack(float& m_enemyHealth);
	void setDamage(float t_dmg) { dmg = t_dmg; }
};

#endif // !WARRIOR