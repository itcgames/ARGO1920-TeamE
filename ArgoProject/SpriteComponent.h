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

// SpriteComponent class deriving from the BaseComponent class,
// since BaseComponent is a template class deriving must be done as shown below
class SpriteComponent : public BaseComponent<SpriteComponent>
{
public:
	SpriteComponent(SDL_Texture* texture, SDL_Rect* rect, int entityID) :
		BaseComponent<SpriteComponent>(entityID),
		m_texture(texture), m_rect(rect), m_isActive(true)
	{

	}

	// Returns the current value of the sprite's rectangle
	SDL_Rect* getRect()
	{
		return m_rect;
	}
	// Returns current value of the sprite's texture
	SDL_Texture* getTexture()
	{
		return m_texture;
	}
	// Sets the value of the sprite's rectangle
	void setRect(SDL_Rect* rect)
	{
		m_rect = rect;
	}
	// Sets the values of the sprite's texture
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
