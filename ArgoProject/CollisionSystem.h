//
// C00204076
// Brandon Seah-Dempsey
// Started at 
// Finished at
// Time taken:
// Known bugs:

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

//#include <vector>

#include "System.h"
#include "Entity.h"
#include "ECS.h"

class Player;

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
			//std::cout << "AABB collision detected" << std::endl;
			return true;
		}
		else
		{
			return false;
		}

		return false;
	}


	void collisionResponse(Entity* m_a, Entity* m_b, int attackTime)
	{

		//player velocity *= -1
		//Vector2 position = m_a->getComponent<PositionComponent>(1)->getPosition();

		//
		/*if (attackTime >= 200)
		{
			position.x += m_b->getComponent<BehaviourComponent>(3)->getNormalizeVel().x * 10;
			position.y += m_b->getComponent<BehaviourComponent>(3)->getNormalizeVel().y * 10;
		}
		//
		else if (attackTime < 200)
		{*/
		/*position.x += m_b->getComponent<BehaviourComponent>(3)->getNormalizeVel().x * 3;
		position.y += m_b->getComponent<BehaviourComponent>(3)->getNormalizeVel().y * 3;
		*///}

		//m_a->getComponent<PositionComponent>(1)->setPosition(position);

		
		if (m_b->getID() == 2)
		{

			m_b->getComponent<StatsComponent>(4)->alterHealth(-1);
		}

	}
	

	void wallCollisionResponse(Entity* m_a, Entity* m_b)
	{
		/*
		speed = joystick_speed()
		old_position = girl.position
		girl.position.x = girl.position.x + speed.x
		collided = tilemap_collision(tilemap, girl.rectangle)
		if(collided)
		{
			girl.position = old_position
		}
		old_position = girl.position
		girl.position.y = girl.position.y + speed.y
		collided = tilemap_collision(tilemap, girl.rectangle)
		if(collided)
		{
			girl.position = old_position
		}
		*/

		Vector2 velocity = m_a->getComponent<BehaviourComponent>(3)->getNormalizeVel();
		Vector2 position = m_a->getComponent<PositionComponent>(1)->getPosition();
		//
		velocity.x *= -1;
		velocity.y *= -1;
		//
		position.x += velocity.x * 9;
		position.y += velocity.y * 9;

		m_a->getComponent<PositionComponent>(1)->setPosition(position);
	}

	void pickupCollisionResponse(Entity* m_a, Entity* m_b)
	{
		if (aabbCollision(m_a->getComponent<SpriteComponent>(2)->getRect(),
			m_b->getComponent<SpriteComponent>(2)->getRect()) == true)
		{
			
			// If type is set to "Health" or "health"...
			if (m_b->getComponent<ItemComponent>(5)->getType() == "Health" || 
				m_b->getComponent<ItemComponent>(5)->getType() == "health")
			{
				//
				/*if (m_b->getComponent<ItemComponent>(5)->getIsSmall() == true)
				{
					//Insert Player logic
					//std::cout << "Small Health collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsMedium() == true)
				{
					//Insert Player logic
					//std::cout << "Medium Health collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsLarge() == true)
				{
					//Insert Player logic
					//std::cout << "Large Health collision" << std::endl;
				}*/

				m_a->getComponent<StatsComponent>(4)->alterHealth(m_b->getComponent<ItemComponent>(5)->getValue());
				m_a->getComponent<HealthComponent>(7)->addHealth(m_b->getComponent<ItemComponent>(5)->getValue());
			}
			
			// If type is set to "Mana" or "mana"...
			else if (m_b->getComponent<ItemComponent>(5)->getType() == "Mana" ||
					 m_b->getComponent<ItemComponent>(5)->getType() == "mana")
			{
				//
				/*if (m_b->getComponent<ItemComponent>(5)->getIsSmall() == true)
				{
					//Insert Player logic
					//std::cout << "Small Mana collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsMedium() == true)
				{
					//Insert Player logic
					//std::cout << "Medium Mana collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsLarge() == true)
				{
					//Insert Player logic
					//std::cout << "Large Mana collision" << std::endl;
				}
				*/

				m_a->getComponent<ManaComponent>(8)->addMana(m_b->getComponent<ItemComponent>(5)->getValue());
			}

			// If type is set to "Stamina" or "stamina"... 
			else if (m_b->getComponent<ItemComponent>(5)->getType() == "Stamina" || 
					 m_b->getComponent<ItemComponent>(5)->getType() == "stamina")
			{
				//
				/*if (m_b->getComponent<ItemComponent>(5)->getIsSmall() == true)
				{
					//Insert Player logic
					//std::cout << "Small Stamina collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsMedium() == true)
				{
					//Insert Player logic
					//std::cout << "Medium Stamina collision" << std::endl;
				}
				//
				else if (m_b->getComponent<ItemComponent>(5)->getIsLarge() == true)
				{
					//Insert Player logic
					//std::cout << "Large Stamina collision" << std::endl;
				}*/

				m_a->getComponent<StaminaComponent>(9)->addStamina(m_b->getComponent<ItemComponent>(5)->getValue());
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

			

		}// End if
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
