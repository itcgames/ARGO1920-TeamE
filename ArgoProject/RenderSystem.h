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

				SDL_RenderCopy(renderer, sprite->getTexture(), NULL, sprite->getRect());
			}
		}
	}

	void renderPlayState(SDL_Renderer* renderer,SDL_Rect* camera, Vector2 positon)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
		}
		SDL_Rect viewableArea = { positon.x, positon.y, 100,100 };
		SDL_RenderCopy(renderer, m_entities[0]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea);
	}
	//
	void renderImage(SDL_Renderer* renderer, SpriteComponent* spriteComponent)
	{
		SDL_RenderCopy(renderer, spriteComponent->getTexture(), NULL, spriteComponent->getRect());
	}

private:
	//
	SDL_Rect* m_position;
	SDL_Texture* m_texture;
	//
	int m_width, m_height;
	int m_x, m_y;
};

#endif // !RENDERSYSTEM_H