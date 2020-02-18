#include "FactoryEnemy.h"

FactoryEnemy::FactoryEnemy()
{
}

FactoryEnemy::~FactoryEnemy()
{
}

std::unique_ptr<IEnemy> FactoryEnemy::createEnemy(ENEMY_TYPE t_enemyType)
{
	switch (t_enemyType)
	{
	case ENEMY_EASY: 
		return std::make_unique<EnemyEasy>();
	case ENEMY_MEDIUM:
		return std::make_unique<EnemyMedium>();
	case ENEMY_HARD:
		return std::make_unique<EnemyHard>();
	default:
		return std::make_unique<EnemyEasy>();
	}
	return std::unique_ptr<IEnemy>();
}
