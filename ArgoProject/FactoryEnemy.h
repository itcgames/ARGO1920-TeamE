#ifndef FACTORYENEMY
#define FATORYENEMY


#include <memory>
#include "IEnemy.h"
#include "EnemyEasy.h"
#include "EnemyMedium.h"
#include "EnemyHard.h"

class FactoryEnemy
{
public:
	enum ENEMY_TYPE { ENEMY_EASY, ENEMY_MEDIUM, ENEMY_HARD };

	FactoryEnemy();

	virtual ~FactoryEnemy();

	static std::unique_ptr<IEnemy> createEnemy(ENEMY_TYPE t_enemyType);
};

#endif // !FACTORYENEMY