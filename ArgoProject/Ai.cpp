#include "Ai.h"


void Ai::initialize(RenderSystem* t_rs)
{
	//draws a rectangle for the enemy
	m_rect = new SDL_Rect();
	m_rect->x = 400; m_rect->y = 400;
	m_rect->w = 100; m_rect->h = 100;

	//loads texture for enemy
	SDL_Surface* ecsSurface2 = IMG_Load("Assets/ecs_text2.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);

	m_enemy = new Entity();
	m_bs = new BehaviourSystem;

	//creates position and sprite components for the enemy
	m_pc = new PositionComponent(Vector2(m_rect->x, m_rect->y), 1);
	m_sc = new SpriteComponent(m_texture, m_rect, 2);
	m_bc = new BehaviourComponent(Vector2(0, 0), 1, 3);

	//adds the new components to the enenmy
	m_enemy->addComponent<PositionComponent>(m_pc, 1);
	m_enemy->addComponent<SpriteComponent>(m_sc, 2);
	m_enemy->addComponent<BehaviourComponent>(m_bc, 3);

	m_bs->addEntity(m_enemy);

	t_rs->addEntity(m_enemy);
	std::cout << "Enemy Initialized" << std::endl;
}

void Ai::update(Vector2 t_position)
{
	m_bs->flee(t_position);
	m_rect->x = m_pc->getPosition().x;
	m_rect->y = m_pc->getPosition().y;
}

void Ai::render()
{
}