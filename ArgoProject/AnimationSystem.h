#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "System.h"
#include "Entity.h"
#include "ECS.h"

//
class AnimationSystem : public System
{
public:
	AnimationSystem()
	{

	}

	void animate(SDL_Rect* t_animationRect, SDL_Rect* t_posRect, int t_spriteSheeyY, int t_frameWidth, int t_speed)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			Uint32 ticks = SDL_GetTicks();
			Uint32 sprite = (ticks / t_speed) % 11;
			t_animationRect->x = sprite * (t_frameWidth);
			t_animationRect->y = t_spriteSheeyY;

			m_entities[i]->getComponent<SpriteComponent>(2)->setRect(t_animationRect);
			m_entities[i]->getComponent<SpriteComponent>(2)->setDstRect(t_posRect);
		}
	}

	Vector2 getFrame(SDL_Rect* t_animationRect)
	{
		return (Vector2(t_animationRect->x, t_animationRect->y));
	}


private:
	SDL_Rect* m_animationRect;
};

#endif // !ANIMATIONSYSTEM_H
