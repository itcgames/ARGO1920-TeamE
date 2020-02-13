//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:20 12 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#include "Pickup.h"

//
void PickUp::initialize(RenderSystem* t_rs, std::string type, bool isSmall, 
	bool isMedium, bool isLarge)
{
	SDL_Surface* ecsSurface2;
	m_rect = new SDL_Rect();
	m_rect->x = 400; m_rect->y = 400;

	// If type is set to "Health" or "health"; loads the health potion texture 
	if (type == "Health" || type == "health")
	{
		ecsSurface2 = IMG_Load("Assets/Health.png");
		m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);
	}
	// If type is set to "Mana" or "mana"; loads the mana potion texture 
	else if (type == "Mana" || type == "mana")
	{
		ecsSurface2 = IMG_Load("Assets/Mana.png");
		m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);
	}
	// If type is set to "Stamina" or "stamina"; loads the stamina potion texture 
	else if (type == "Stamina" || type == "stamina")
	{
		ecsSurface2 = IMG_Load("Assets/Stamina.png");
		m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);
	}
	//  If type is set to "Gold" or "gold"; loads the gold bag texture 
	else if (type == "Gold" || type == "gold")
	{
		ecsSurface2 = IMG_Load("Assets/Gold.png");
		m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);
	}
	// Else if type is not set to any previously mentioned values, texture is defaulted
	// to health potion
	else
	{
		ecsSurface2 = IMG_Load("Assets/Health.png");
		m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface2);
	}

	//
	if (isSmall == true)
	{
		m_rect->w = 20; m_rect->h = 20;
	}
	//
	else if (isMedium == true)
	{
		m_rect->w = 25; m_rect->h = 25;
	}
	//
	else if (isLarge == true)
	{
		m_rect->w = 40; m_rect->h = 40;
	}
	// Else if none of these booleans are true; isSmall will be defaulted 
	else
	{
		isSmall == true;
		m_rect->w = 20; m_rect->h = 20;
	}
	
	//
	m_item = new Entity();
	//
	m_pc = new PositionComponent(Vector2(m_rect->x, m_rect->y), 1);
	m_sc = new SpriteComponent(m_texture, m_rect, 2);
	m_ic = new ItemComponent(type, isSmall, isMedium, isLarge, 5);
	//
	m_item->addComponent<PositionComponent>(m_pc, 1);
	m_item->addComponent<SpriteComponent>(m_sc, 2);
	m_item->addComponent<ItemComponent>(m_ic, 5);
	//
	t_rs->addEntity(m_item);

	std::cout << "Item Initialize" << std::endl;
}

//
void PickUp::update()
{

	m_rect->x = m_pc->getPosition().x;
	m_rect->y = m_pc->getPosition().y;
}

//
void PickUp::destroy()
{

	
	delete this;
}

//
Entity* PickUp::getEntity()
{
	return m_item;
}

//
SDL_Rect* PickUp::getRect()
{
	return m_rect;
}