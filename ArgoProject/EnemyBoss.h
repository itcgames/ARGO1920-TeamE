#ifndef ENEMYBOSS
#define ENEMYBOSS


#include "IEnemy.h"

class EnemyBoss : public IEnemy
{
public:
	EnemyBoss();
	virtual ~EnemyBoss();
	void initialize(RenderSystem* t_rs, Vector2 t_Position, std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount);
	void update(Vector2 t_position);
	Entity* getEntity() { return m_enemy; }
	void destroy() { delete this; }
	int getAttackTime();
	void setAttackTime(int attackTime);
	bool getSeek();
	void setSeek(bool seek);

	int getRoom() { return roomNum; }
	void setRoom(int roomNumber) { roomNum = roomNumber; }
};

#endif // !ENEMYBOSS