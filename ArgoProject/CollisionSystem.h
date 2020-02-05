//
// C00204076
// Brandon Seah-Dempsey
// Started at 
// Finished at
// Time taken:
// Known bugs:

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <vector>

#include "System.h"
#include "Entity.h"
#include "ECS.h"

//
class CollisionSystem : public System
{
public:
	CollisionSystem()
	{

	}

	// Detects collisions of each side of Entity's rectangle; Bounding Box
	// m_rect may appear as an error but is not an actual error
	bool collisionDetect(Entity* m_rect)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_position.x = m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x;
			m_position.y = m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y;

			/*// Top side collision
			if (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y >= m_rect->getComponent<PositionComponent>(1)->getPosition().y + m_rect->getComponent<SpriteComponent>(2)->getRect().h)
			{
				return 0;
			}
			// Left side collision
			if (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x >= m_rect->getComponent<PositionComponent>(1)->getPosition().x + m_rect->getComponent<SpriteComponent>(2)->getRect().w)
			{
				return 0;
			}
			// Bottom side collision
			if (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y + m_entities[i]->getComponent<SpriteComponent>(2)->getRect().h >= m_rect->getComponent<PositionComponent>(1)->getPosition().y)
			{
				return 0;
			}
			// Right side collision
			if (m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x + m_entities[i]->getComponent<SpriteComponent>(2)->getRect().w >= m_rect->getComponent<PositionComponent>(1)->getPosition().x)
			{
				return 0;
			}

			return 1;*/

			// 
			int leftOne = m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x;
			int rightOne = m_entities[i]->getComponent<PositionComponent>(1)->getPosition().x + m_entities[i]->getComponent<SpriteComponent>(2)->getRect().w;
			int topOne = m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y;
			int bottomOne = m_entities[i]->getComponent<PositionComponent>(1)->getPosition().y + m_entities[i]->getComponent<SpriteComponent>(2)->getRect().h;
			//
			int leftTwo = m_rect->getComponent<PositionComponent>(1)->getPosition().x;
			int rightTwo = m_rect->getComponent<PositionComponent>(1)->getPosition().x + m_rect->getComponent<SpriteComponent>(2)->getRect().w;
			int topTwo = m_rect->getComponent<PositionComponent>(1)->getPosition().y;
			int bottomTwo = m_rect->getComponent<PositionComponent>(1)->getPosition().y + m_rect->getComponent<SpriteComponent>(2)->getRect().h;

			// Check edges
			// leftOne is right of rightTwo
			if (leftOne > rightTwo) 
			{
				m_position.x += 1;
				m_entities[i]->getComponent<PositionComponent>(1)->setPosition(m_position);
				return false; // No collision
			}
			// rightOne is left of leftTwo
			if (rightOne < leftTwo)
			{
				m_position.x -= 1;
				m_entities[i]->getComponent<PositionComponent>(1)->setPosition(m_position);
				return false; // No collision
			}
			// topOne is below bottomTwo
			if (topOne > bottomTwo)
			{
				m_position.y += 1;
				m_entities[i]->getComponent<PositionComponent>(1)->setPosition(m_position);
				return false; // No collision
			}
			// bottomOne is above topTwo 
			if (bottomOne < topTwo) 
			{
				m_position.y -= 1;
				m_entities[i]->getComponent<PositionComponent>(1)->setPosition(m_position);
				return false; // No collision
			}

			return true;
		}

		/*
		bool b[4] = {0,0,0,0};

		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
					case SDLK_UP:
							b[0] = 1;
							break;
					case SDLK_LEFT:
							b[1] = 1;
							break;
					case SDLK_DOWN:
							b[2] = 1;
							break;
					case SDLK_RIGHT:
							b[3] = 1;
							break;

			}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_UP:
							b[0] = 0;
							break;
					case SDLK_LEFT:
							b[1] = 0;
							break;
					case SDLK_DOWN:
							b[2] = 0;
							break;
					case SDLK_RIGHT:
							b[3] = 0;
							break;

		 //logic
                if(b[0]) {
                        rect.y--;
                        for(int i = 0; i < 5; i += 1)
                                if(collision(&rect,&recarr[i]))
                                        rect.y++;
                }
                if(b[1]) {
                        rect.x--;
                        for(int i = 0; i < 5; i += 1)
                                if(collision(&rect,&recarr[i]))
                                        rect.x++;
                }
                if(b[2]) {
                        rect.y++;
                        for(int i = 0; i < 5; i += 1)
                                if(collision(&rect,&recarr[i]))
                                        rect.y--;
                }
                if(b[3]) {
                        rect.x++;
                        for(int i = 0; i < 5; i += 1)
                                if(collision(&rect,&recarr[i]))
                                        rect.x--;
                }
		*/
	}


private:
	//
	SDL_Rect* m_position;
	SDL_Rect* m_rect;
	//
	int m_width, m_height;
	int m_x, m_y;

};

#endif // !COLLISIONSYSTEM_H
