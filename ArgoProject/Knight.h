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
	void animate();
	void processEvents(bool isRunning);
	Vector2 getPosition() { return m_pc->getPosition(); }
	Entity* getEntity() { return m_player; }
	void setAction();
	//void hit(Entity* t_enemy);
	SDL_Rect* getRect() { return m_positionRect; }
};

#endif // !KNIGHT