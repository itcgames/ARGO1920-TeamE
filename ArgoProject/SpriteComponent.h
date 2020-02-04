//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:18 3 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"


class SpriteComponent : public BaseComponent<SpriteComponent>
{
public:
	SpriteComponent(SDL_Texture* texture, SDL_Rect* rect, int entityID) :
		BaseComponent<SpriteComponent>(entityID),
		m_texture(texture), m_rect(rect), m_isActive(true)
	{

	}

	SDL_Rect* getRect()
	{
		return m_rect;
	}

	SDL_Texture* getTexture()
	{
		return m_texture;
	}

	void setRect(SDL_Rect* rect)
	{
		m_rect = rect;
	}

	void setTexture(SDL_Texture* texture)
	{
		m_texture = texture;
	}

private:
	bool m_isActive;
	SDL_Texture* m_texture;
	SDL_Rect* m_rect;

};

#endif // !SPRITECOMPONENT_H
