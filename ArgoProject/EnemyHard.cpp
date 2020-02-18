#include "EnemyHard.h"

EnemyHard::EnemyHard()
{
}

EnemyHard::~EnemyHard()
{
}

void EnemyHard::initialize(RenderSystem* t_rs, Vector2 t_Position, std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount)
{
	//draws a rectangle for the enemy
	m_rect = new SDL_Rect();
	m_rect->x = t_Position.x; m_rect->y = t_Position.y;
	m_rect->w = 100; m_rect->h = 100;

	//loads texture for enemy
	SDL_Surface* ecsSurface2 = IMG_Load("Assets/ecs_text2.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);

	m_enemy = new Entity();
	m_bs = new BehaviourSystem;

	//creates position and sprite components for the enemy
	m_pc = new PositionComponent(Vector2(m_rect->x, m_rect->y), 1);
	m_sc = new SpriteComponent(m_texture, m_rect, 2);
	m_bc = new BehaviourComponent(Vector2(0, 0), 1, 0, 3);
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

	t_rs->addEntity(m_enemy);
	std::cout << "Enemy Initialized" << std::endl;
}

void EnemyHard::update(Vector2 t_position)
{
	Vector2 newVec = (t_position.x - m_enemy->getComponent<PositionComponent>(1)->getPosition().x,
		t_position.y - m_enemy->getComponent<PositionComponent>(1)->getPosition().y);

	m_normalizedVec = m_normalizedVec.normalize(newVec);

	//m_bs->flee(t_position);
	m_bs->seek(t_position);
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

int EnemyHard::getAttackTime()
{
	return m_attackTime;
}

void EnemyHard::setAttackTime(int attackTime)
{
	m_attackTime = attackTime;
}
