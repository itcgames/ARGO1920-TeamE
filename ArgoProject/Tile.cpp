#include "Tile.h"

Tile::Tile(Vector2 pos,int width,int height,std::string path,std::string tileTag, RenderSystem* t_rs, CollisionSystem* t_cs)
{
	endRect = new SDL_Rect();
	tag = tileTag;
	HEIGHT = height;
	WIDTH = width;
	m_position = pos;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	img = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), tempSurface);

	SDL_FreeSurface(tempSurface);

	endRect->x = m_position.x;
	endRect->y = m_position.y;

	endRect->w  = width;
	endRect->h  = height;

	m_tile = new Entity();

	m_pc = new PositionComponent(Vector2(endRect->x, endRect->y), 1);
	m_sc = new SpriteComponent(img, endRect, 2);
	m_ac = new ActiveComponent(true,6);

	m_tile->addComponent<PositionComponent>(m_pc,1);
	m_tile->addComponent<SpriteComponent>(m_sc, 2);
	m_tile->addComponent<ActiveComponent>(m_ac, 6);

	t_rs->addEntity(m_tile);

	if (tag == "Wall")
	{
		t_cs->addEntity(m_tile);
	}

}

Tile::~Tile()
{
	SDL_DestroyTexture(img);
}

void Tile::render()
{
	//SDL_RenderCopy(Render::Instance()->getRenderer(), img, &startRect, endRect);
}

Vector2 Tile::getPos()
{
	return m_position;
}

int Tile::getHeight()
{
	return HEIGHT;
}

int Tile::getWidth()
{
	return WIDTH;
}

std::string Tile::getTag()
{
	return tag;
}

