#ifndef ENEMYHARD
#define ENEMYHARD

#include "IEnemy.h"

class EnemyHard : public IEnemy
{
public:
	EnemyHard();
	virtual ~EnemyHard();
	void initialize(RenderSystem* t_rs, Vector2 t_Position, std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount);
	void update(Vector2 t_position);
	Entity* getEntity() { return m_enemy; }
	void destroy() { delete this; }
	int getAttackTime();
	void setAttackTime(int attackTime);
	bool getSeek();
	void setSeek(bool seek);
};

#endif // !ENEMYHARD