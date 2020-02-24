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

	void setDstRect(SDL_Rect* dstRect)
	{
		m_dstrect = dstRect;
	}

	SDL_Rect* getDstRect()
	{
		return m_dstrect;
	}

	void animate(SDL_Rect *t_animationRect, SDL_Rect *t_posRect, int t_spriteSheeyY, int t_frameWidth)
	{
		Uint32 ticks = SDL_GetTicks();
		Uint32 sprite = (ticks / 100) % 11;
		t_animationRect->x = sprite * (t_frameWidth);
		t_animationRect->y = t_spriteSheeyY;

		setRect(t_animationRect);
		setDstRect(t_posRect);
	}

private:
	bool m_isActive;
	SDL_Texture* m_texture;
	SDL_Rect* m_rect;
	SDL_Rect* m_dstrect;

};

#endif // !SPRITECOMPONENT_H
