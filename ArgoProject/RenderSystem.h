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
	std::vector<Entity*> m_minimapList;
	TTF_Font* font;
	SDL_Color White;
	SDL_Surface* enemyHealthSurface;
	SDL_Texture* enemyHealthText;
	//
	RenderSystem()
	{
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}

		font = TTF_OpenFont("Assets/Font/Abel.ttf", 100);

		if (!font) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			// handle error
		}

		White = { 255, 255, 255 };
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
		//SDL_Rect viewableArea = { positon.x, positon.y, 100,100 };
		//SDL_RenderCopy(renderer, m_entities[0]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea);
		//SDL_RenderSetViewport(renderer, camera);
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
				m_minimapList.push_back(m_entities[i]);

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

				if (m_entities[i]->getID() != 1)
				{
					SDL_RenderCopyEx(renderer, m_entities[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);
				}
				else
				{
					playerID = i;
					SDL_RenderCopyEx(renderer, m_entities[playerID]->getComponent<SpriteComponent>(2)->getTexture(), m_entities[playerID]->getComponent<SpriteComponent>(2)->getRect(), &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);
				}

				if (m_entities[i]->getID() == 2)
				{
					std::string m_health = std::to_string(m_entities[i]->getComponent<StatsComponent>(4)->getHealth());
					enemyHealthSurface = TTF_RenderText_Solid(font, m_health.c_str(), White);

					enemyHealthText = SDL_CreateTextureFromSurface(renderer, enemyHealthSurface);

					SDL_RenderCopyEx(renderer, enemyHealthText, NULL, &viewableArea, angle, NULL, SDL_FLIP_NONE);
				}
			}
		}

		t_hud->render();

		 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 //Draws the minimap

		viewableArea = { miniMap->x - 100, miniMap->y - 100, miniMap->w * 2,miniMap->h * 2 };
		SDL_RenderCopy(renderer, t_miniMapTexture,NULL,&viewableArea);

		for (int i = 0; i < m_minimapList.size(); i++)
		{
			int posX = ((m_minimapList[i]->getComponent<PositionComponent>(1)->getPosition().x) / 20) + camera->w - miniMap->w * 2;
			int posY = ((m_minimapList[i]->getComponent<PositionComponent>(1)->getPosition().y) / 20) + camera->h - miniMap->h * 2;
		
			viewableArea = { posX, posY, m_minimapList[i]->getComponent<SpriteComponent>(2)->getRect()->w / 20,m_minimapList[i]->getComponent<SpriteComponent>(2)->getRect()->h / 20 };

			if (m_minimapList[i]->getComponent<BehaviourComponent>(3) != NULL)
			{
				angle = m_minimapList[i]->getComponent<BehaviourComponent>(3)->getRotationAngle();
			}
			else
			{
				angle = 0;
			}

			//SDL_RenderCopyEx(renderer, m_minimapList[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea, angle, NULL, SDL_FLIP_HORIZONTAL);
			if (m_minimapList[i]->getID() != 1)
			{
				SDL_RenderCopyEx(renderer, m_minimapList[i]->getComponent<SpriteComponent>(2)->getTexture(), NULL, &viewableArea, angle, NULL, SDL_FLIP_NONE);
			}
			else
			{
				playerID = i;
				SDL_RenderCopyEx(renderer, m_minimapList[playerID]->getComponent<SpriteComponent>(2)->getTexture(), m_minimapList[playerID]->getComponent<SpriteComponent>(2)->getRect(), &viewableArea, angle, NULL, SDL_FLIP_NONE);
			}
		}
		m_minimapList.clear();
	}

	//
	void renderImage(SDL_Renderer* renderer, SpriteComponent* spriteComponent)
	{
		SDL_RenderCopyEx(renderer, spriteComponent->getTexture(), NULL, spriteComponent->getRect(), 0, NULL, SDL_FLIP_NONE);
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