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

	void animate(SDL_Rect* t_animationRect, SDL_Rect* t_posRect, int t_spriteSheetY, int t_frameWidth, int t_speed, int state, int aTimer)
	{
		//Uint32 ticks = 0;
		//Uint32 sprite = 0;
		//t_animationRect->x = 0;
		for (int i = 0; i < m_entities.size(); i++)
		{
			Uint32 ticks = SDL_GetTicks();
			if (m_entities[i]->getID() == 1 && (state != 0 || state != 1) && ticks - aTimer < 1401)
			{
				ticks -= aTimer;
			}

			Uint32 sprite = (ticks / t_speed) % 11;
			t_animationRect->x = sprite * (t_frameWidth);
			t_animationRect->y = t_spriteSheetY;
			m_entities[i]->getComponent<SpriteComponent>(2)->setRect(t_animationRect);
			m_entities[i]->getComponent<SpriteComponent>(2)->setDstRect(t_posRect);
		}
	}
};

#endif // !ANIMATIONSYSTEM_H
