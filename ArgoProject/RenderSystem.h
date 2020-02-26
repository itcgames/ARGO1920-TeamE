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
#include <SDL_ttf.h>
#include "System.h"
#include "Entity.h"
#include "BehaviourComponent.h"
#include "HUD.h"

class RenderSystem : public System
{
public:
	std::vector<Entity*> m_miniMapList;
	SDL_Surface* healthSurface;
	SDL_Texture* healthTexture;
	Vector2 m_miniMapRatio;
	//
	RenderSystem(SDL_Renderer* renderer, Vector2 t_miniMapRatio)
	{
		m_miniMapRatio = t_miniMapRatio;
		healthSurface = IMG_Load("Assets/ecs_text.png");
		healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);
	}

	//
	void render(SDL_Renderer* renderer)
	{


		if (m_entities.back()->getComponent<PositionComponent>(1)->getPosition().x + m_entities.back()->getComponent<SpriteComponent>(2)->getRect()->w < 0)
		{

		}
		else
		{
			SpriteComponent* sprite = m_entities.back()->getComponent<SpriteComponent>(2);
			if (m_entities.back()->getComponent<BehaviourComponent>(3) != NULL)
			{
				angle = m_entities.back()->getComponent<BehaviourComponent>(3)->getRotationAngle();
			}
			else
			{
				angle = 0;
			}
			SDL_RenderCopyEx(renderer, sprite->getTexture(), sprite->getRect(), sprite->getDstRect(), angle, NULL, SDL_FLIP_NONE);
		}
	}

	void renderPlayState(SDL_Renderer* renderer, SDL_Rect* camera, SDL_Rect* miniMap, SDL_Texture* t_miniMapTexture, HUD* t_hud)//, Vector2 positon)
	{
		m_miniMapList.clear();
		int playerID = 0;
		for (int i = 0; i < m_entities.size(); i++)
		{

			if ((m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x + m_entities[i]->getComponent<SpriteComponent>(2)->getRect()->w < camera->x
				||
				(m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x > camera->x + camera->w))
				||
				(m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y + m_entities[i]->getComponent<SpriteComponent>(2)->getRect()->h < camera->y
					||
					(m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y > camera->y + camera->h)))
			{

			}
			else
			{
				if (m_entities[i]->getComponent<BehaviourComponent>(3) != NULL)
				{
					angle = m_entities[i]->getComponent<BehaviourComponent>(3)->getRotationAngle();
				}
				else
				{

					angle = 0;
				}
				m_miniMapList.push_back(m_entities[i]);

				int posX = (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x - camera->x);
				int posY = (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y - camera->y);
				viewableArea = { posX, posY, m_entities[i]->getComponent<SpriteComponent>(2)->getRect()->w,m_entities[i]->getComponent<SpriteComponent>(2)->getRect()->h };

				if (m_entities[i]->getComponent<BehaviourComponent>(3) != NULL)
				{
					angle = m_entities[i]->getComponent<BehaviourComponent>(3)->getRotationAngle();
				}
				else
				{
					angle = 0;
				}

				if (m_entities[i]->getID() != 1 && m_entities[i]->getID() != 2)
				{
					SDL_RenderCopyEx(renderer, m_entities[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);
				}
				else if (m_entities[i]->getID() == 2)
				{
					if (m_entities[i]->getComponent<ActiveComponent>(6)->getIsActive())
					{
						SDL_RenderCopyEx(renderer, m_entities[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);

						viewableArea.y -= 20;
						viewableArea.h = 10;
						viewableArea.w = (m_entities[i]->getComponent<HealthComponent>(5)->getHealth() / m_entities[i]->getComponent<HealthComponent>(5)->getOriginalHealth()) * viewableArea.w;

						SDL_RenderCopyEx(renderer, healthTexture, NULL, &viewableArea, 0, NULL, SDL_FLIP_NONE);
					}
				}
				else
				{
					SDL_RenderCopyEx(renderer, m_entities[i]->getComponent<SpriteComponent>(2)->getTexture(), m_entities[i]->getComponent<SpriteComponent>(2)->getRect(), &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);

					/*if (m_entities[i]->getComponent<ActiveComponent>(6)->getIsActive())
					{ 
						viewableArea.y -= 20;
						viewableArea.h = 10;
						viewableArea.w = (m_entities[i]->getComponent<HealthComponent>(5)->getHealth() / m_entities[i]->getComponent<HealthComponent>(5)->getOriginalHealth()) * viewableArea.w;

						SDL_RenderCopyEx(renderer, healthTexture, NULL, &viewableArea, 0, NULL, SDL_FLIP_NONE);
					}*/
				}
			}
		}

		t_hud->render();

		 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 //Draws the minimap

		viewableArea = { miniMap->x, miniMap->y, miniMap->w,miniMap->h };
		SDL_RenderCopy(renderer, t_miniMapTexture,NULL,&viewableArea);

		for (int i = 0; i < m_miniMapList.size(); i++)
		{
			int posX = ((m_miniMapList[i]->getComponent<PositionComponent>(1)->getPosition().x) / m_miniMapRatio.x) + miniMap->x;
			int posY = ((m_miniMapList[i]->getComponent<PositionComponent>(1)->getPosition().y) / m_miniMapRatio.y) + miniMap->y;
			int width = m_miniMapList[i]->getComponent<SpriteComponent>(2)->getRect()->w / m_miniMapRatio.x + 1;
			int height = m_miniMapList[i]->getComponent<SpriteComponent>(2)->getRect()->h / m_miniMapRatio.y + 1;
			//std::cout << posX << " " << posY << std::endl;
			viewableArea = { posX, posY, width,height};

			if (m_miniMapList[i]->getComponent<BehaviourComponent>(3) != NULL)
			{
				angle = m_miniMapList[i]->getComponent<BehaviourComponent>(3)->getRotationAngle();
			}
			else
			{
				angle = 0;
			}

			//SDL_RenderCopyEx(renderer, m_minimapList[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);
			if (m_miniMapList[i]->getID() != 1)
			{
				SDL_RenderCopyEx(renderer, m_miniMapList[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea, angle, NULL, SDL_FLIP_NONE);
			}
			else
			{
				SDL_RenderCopyEx(renderer, m_miniMapList[i]->getComponent<SpriteComponent>(2)->getTexture(), m_miniMapList[i]->getComponent<SpriteComponent>(2)->getRect(), &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);
			}
		}
	}

	//
	void renderImage(SDL_Renderer* renderer, SpriteComponent* spriteComponent)
	{
		SDL_RenderCopyEx(renderer, spriteComponent->getTexture(), NULL, spriteComponent->getRect(), 0, NULL, SDL_FLIP_NONE);
	}

	void clearMap()
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			SDL_DestroyTexture(m_entities[i]->getComponent<SpriteComponent>(2)->getTexture());
			/*delete m_entities[i]->getComponent<PositionComponent>(1);
			delete m_entities[i]->getComponent<SpriteComponent>(2);
			if (m_entities[i]->getID() == 2)
			{
				delete m_entities[i]->getComponent<BehaviourComponent>(3);
				delete m_entities[i]->getComponent<StatsComponent>(4);
				delete m_entities[i]->getComponent<HealthComponent>(5);
				delete m_entities[i]->getComponent<ActiveComponent>(6);
			}
			else if (m_entities[i]->getID() == 1)
			{
				delete m_entities[i]->getComponent<BehaviourComponent>(3);
				delete m_entities[i]->getComponent<StatsComponent>(4);
				delete m_entities[i]->getComponent<HealthComponent>(5);
				delete m_entities[i]->getComponent<ActiveComponent>(6);
				delete m_entities[i]->getComponent<ManaComponent>(7);
				delete m_entities[i]->getComponent<StaminaComponent>(8);
			}*/
		}
	}

private:
	//
	
	SDL_Rect viewableArea = { 0, 0, 100,100 };
	SDL_Rect* m_position;
	SDL_Texture* m_texture;
	//
	int m_width, m_height;
	int m_x, m_y;
	float angle;
};

#endif // !RENDERSYSTEM_H