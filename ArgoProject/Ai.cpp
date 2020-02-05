#include "Ai.h"

void Ai::initialize(RenderSystem* t_rs)
{
	//draws a rectangle for the enemy
	m_enemyRect = new SDL_Rect();
	m_enemyRect->x = 400; m_enemyRect->y = 400;
	m_enemyRect->w = 100; m_enemyRect->h = 100;

	//loads texture for enemy
	SDL_Surface* ecsSurface2 = IMG_Load("Assets/ecs_text2.png");
	m_enemyTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);

	m_enemy = new Entity();

	//creates position and sprite components for the enemy
	m_enemyPc = new PositionComponent(Vector2(m_enemyRect->x, m_enemyRect->y), 1);
	m_enemySc = new SpriteComponent(m_enemyTexture, m_enemyRect, 2);

	//adds the new components to the enenmy
	m_enemy->addComponent<PositionComponent>(m_enemyPc, 1);
	m_enemy->addComponent<SpriteComponent>(m_enemySc, 2);

	t_rs->addEntity(m_enemy);

	std::cout << "Enemy Initialized" << std::endl;
}

void Ai::update()
{
}

void Ai::render()
{
}
