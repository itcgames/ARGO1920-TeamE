#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

//#include <vector>

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
	bool aabbCollision(SDL_Rect* m_a, SDL_Rect* m_b)
	{
		//
		if (m_a->x + m_a->w >= m_b->x &&
			m_b->x + m_b->w >= m_a->x &&
			m_a->y + m_a->h >= m_b->y &&
			m_b->y + m_b->h >= m_a->y)
		{
			return true;
		}
		else
		{
			return false;
		}

		return false;
	}


	void collisionResponse(Entity* m_a, Entity* m_b, bool seek)
	{

		Vector2 position = m_a->getComponent<PositionComponent>(1)->getPosition();
		Vector2 velocity = m_a->getComponent<BehaviourComponent>(3)->getNormalizeVel();

		if (m_b->getID() == 2)
		{
			if (m_b->getID() == 2 && m_a->getID() == 1)
			{
				m_a->getComponent<HealthComponent>(5)->alterHealth(-0.1f);
			}

		}
	}

	bool enemyCollisionResponse(SDL_Rect* m_a, Entity* m_b, Vector2 m_aPos)
	{
		//
		if ((m_aPos.x < m_b->getComponent<PositionComponent>(1)->getPosition().x + 480 && m_aPos.x > m_b->getComponent<PositionComponent>(1)->getPosition().x - 480) &&
			(m_aPos.y < m_b->getComponent<PositionComponent>(1)->getPosition().y + 480 && m_aPos.y > m_b->getComponent<PositionComponent>(1)->getPosition().x - 480))
		{
			if (m_a->x + m_a->w >= m_b->getComponent<PositionComponent>(1)->getPosition().x &&
				m_a->y + m_a->h >= m_b->getComponent<PositionComponent>(1)->getPosition().y &&
				m_b->getComponent<PositionComponent>(1)->getPosition().x + m_b->getComponent<SpriteComponent>(2)->getRect()->w >= m_a->x &&
				m_b->getComponent<PositionComponent>(1)->getPosition().y + m_b->getComponent<SpriteComponent>(2)->getRect()->h >= m_a->y)
			{
				return true;
			}
		}
		else
		{
			return false;
		}

		/*
		if ((t_targetPosition.x < position.x + 300 && t_targetPosition.x > position.x - 300) &&
			(t_targetPosition.y < position.y + 300 && t_targetPosition.y > position.y - 300)
		*/
	}

	void wallCollisionResponse(Entity* m_a, Entity* m_b)
	{
		Vector2 velocity = m_a->getComponent<BehaviourComponent>(3)->getNormalizeVel();
		Vector2 position = m_a->getComponent<PositionComponent>(1)->getPosition();
		//
		position += velocity * -1 * 24;

		m_a->getComponent<PositionComponent>(1)->setPosition(position);
	}

	void pickupCollisionResponse(Entity* m_a, Entity* m_b)
	{

			if (m_b->getComponent<ItemComponent>(5)->getType() == "Health" || 
				m_b->getComponent<ItemComponent>(5)->getType() == "health")
			{
				m_a->getComponent<HealthComponent>(5)->alterHealth(m_b->getComponent<ItemComponent>(5)->getValue());
			}

			//  If type is set to "Gold" or "gold"...
			else if (m_b->getComponent<ItemComponent>(5)->getType() == "Gold" || 
				     m_b->getComponent<ItemComponent>(5)->getType() == "gold")
			{
				//
				/*if (m_b->getComponent<ItemComponent>(5)->getIsSmall() == true)
				{
					//Insert Player logic
					//std::cout << "Small Gold collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsMedium() == true)
				{
					//Insert Player logic
					//std::cout << "Medium Gold collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsLarge() == true)
				{
					//Insert Player logic
					//std::cout << "Large Gold collision" << std::endl;
				}*/

				m_a->getComponent<StatsComponent>(4)->addGold(m_b->getComponent<ItemComponent>(5)->getValue());
			}

			

		
	}

	// Separating Axis Theorem Collision
	/*void getAxis()
	{
		float axis = {};
	}

	void getCorners(SDL_Rect* m_rect)
	{
		Vector2 corners = {};
		

	}

	float dotProduct(SDL_Rect* m_a, SDL_Rect* m_b)
	{
		return (m_a->x * m_b->x) + (m_a->y * m_b->y);
	}*/



private:
	//
	SDL_Rect* m_position;
	SDL_Rect* m_rect;
	//
	int m_width, m_height;
	int m_x, m_y;

};

#endif // !COLLISIONSYSTEM_H
