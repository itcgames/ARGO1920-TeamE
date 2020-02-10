//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:18 3 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>

#include "System.h"
#include "Entity.h"
#include "BehaviourComponent.h"
//#include "ECS.h"

class RenderSystem : public System
{
public:
	//
	RenderSystem()
	{
	}

	//
	void render(SDL_Renderer* renderer)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			
			if (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x + m_entities[i]->getComponent<SpriteComponent>(2)->getRect()->w < 0)
			{
				m_entities[i] = nullptr;
				m_entities.erase(m_entities.begin() + i);
				i--;
			}
			else
			{
				SpriteComponent* sprite = m_entities[i]->getComponent<SpriteComponent>(2);
				if (m_entities[i]->getComponent<BehaviourComponent>(3) != NULL)
				{
					angle = m_entities[i]->getComponent<BehaviourComponent>(3)->getRotationAngle();
				}
				else
				{
					angle = 0;
				}
				SDL_RenderCopyEx(renderer, sprite->getTexture(), NULL, sprite->getRect(), angle, NULL, SDL_FLIP_HORIZONTAL);
			}
		}
	}

	void renderPlayState(SDL_Renderer* renderer,SDL_Rect* camera, Vector2 positon)
	{
		SDL_Rect viewableArea = { positon.x, positon.y, 100,100 };
		SDL_RenderCopy(renderer, m_entities[0]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea);

		for (int i = 1; i < m_entities.size(); i++)
		{
			int posX = (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x - camera->x);
			int posY = (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y - camera->y);
			viewableArea = { posX, posY, 100,100 };
			SDL_RenderCopy(renderer, m_entities[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea);
		}
	}
	//
	void renderImage(SDL_Renderer* renderer, SpriteComponent* spriteComponent)
	{
		SDL_RenderCopyEx(renderer, spriteComponent->getTexture(), NULL, spriteComponent->getRect(), 0, NULL, SDL_FLIP_NONE);
	}

private:
	//
	SDL_Rect* m_position;
	SDL_Texture* m_texture;
	//
	int m_width, m_height;
	int m_x, m_y;
	float angle;
};

#endif // !RENDERSYSTEM_H