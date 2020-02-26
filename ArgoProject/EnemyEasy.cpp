#include "EnemyEasy.h"

EnemyEasy::EnemyEasy()
{
}

EnemyEasy::~EnemyEasy()
{
}

void EnemyEasy::initialize(RenderSystem* t_rs, Vector2 t_Position, std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount)
{
	//draws a rectangle for the enemy
	m_rect = new SDL_Rect();
	m_rect->x = t_Position.x; m_rect->y = t_Position.y;
	m_rect->w = 10; m_rect->h = 10;

	//loads texture for enemy
	SDL_Surface* ecsSurface2 = IMG_Load("Assets/Zombie2.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);

	m_enemy = new Entity();
	m_bs = new BehaviourSystem;

	finiteStateMachine = new FSM();
	state = new FiniteState();

	finiteStateMachine->idle();

	//creates position and sprite components for the enemy
	m_pc = new PositionComponent(Vector2(m_rect->x, m_rect->y), 1);
	m_sc = new SpriteComponent(m_texture, m_rect, 2);
	m_bc = new BehaviourComponent(Vector2(0, 0), 1, 0, t_speed);
	m_statsC = new StatsComponent(t_class, t_health, t_strength, t_speed, t_gold, t_killCount, 4);
	m_hc = new HealthComponent(t_health, 5);
	m_ac = new ActiveComponent(true, 6);

	//adds the new components to the enenmy
	m_enemy->setID(2);
	m_enemy->addComponent<PositionComponent>(m_pc, 1);
	m_enemy->addComponent<SpriteComponent>(m_sc, 2);
	m_enemy->addComponent<BehaviourComponent>(m_bc, 3);
	m_enemy->addComponent<StatsComponent>(m_statsC, 4);
	m_enemy->addComponent<HealthComponent>(m_hc, 5);
	m_enemy->addComponent<ActiveComponent>(m_ac, 6);

	m_bs->addEntity(m_enemy);

	m_seek = true;

	t_rs->addEntity(m_enemy);
	m_enemySound.load("Assets/Audio/Zombie.wav");
	std::cout << "Enemy Initialized" << std::endl;
}

void EnemyEasy::update(Vector2 t_position)
{
	Vector2 newVec = (t_position.x - m_enemy->getComponent<PositionComponent>(1)->getPosition().x,
		t_position.y - m_enemy->getComponent<PositionComponent>(1)->getPosition().y);
	float distance = sqrt((newVec.x * newVec.x) + (newVec.y * newVec.y));
	if (distance < 350)
	{
		//m_enemySound.play();
	}
	else
	{
		//m_enemySound.stop();
	}
	m_normalizedVec = m_normalizedVec.normalize(newVec);
	//This is to stop the jittering in the movement.         
	float mag = sqrt((m_pc->getPosition().x - t_position.x) * (m_pc->getPosition().x - t_position.x) + (m_pc->getPosition().y - t_position.y) * (m_pc->getPosition().y - t_position.y));
	if (mag > 100 && mag < 1000)
	{
		finiteStateMachine->walking();
		m_bs->seek(t_position);
	}
	else
	{
		finiteStateMachine->idle();
	}
	if(mag < 100)
	{
		finiteStateMachine->skillone();
	}
	//m_bs->enemySeek(t_position, m_normalizedVec, m_attackTime);
	m_rect->x = m_pc->getPosition().x;
	m_rect->y = m_pc->getPosition().y;

	if (m_attackTime < 200)
	{
		m_attackTime++;
	}

	if (m_enemy->getComponent<HealthComponent>(5)->getHealth() <= 0)
	{
		m_enemy->getComponent<ActiveComponent>(6)->setIsActive(false);
	}
}

int EnemyEasy::getAttackTime()
{
	return m_attackTime;
}

void EnemyEasy::setAttackTime(int attackTime)
{
	m_attackTime = attackTime;
}

bool EnemyEasy::getSeek()
{
	return m_seek;
}

void EnemyEasy::setSeek(bool seek)
{
	m_seek = seek;
}


