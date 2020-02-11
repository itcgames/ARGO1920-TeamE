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

		return false;
	}

	void collisionResponse(Entity* m_a, Entity* m_b)
	{
		if (aabbCollision(m_a->getComponent<SpriteComponent>(2)->getRect(),
			m_b->getComponent<SpriteComponent>(2)->getRect()) == true)
		{
			//std::cout << "Enemy collision detected" << std::endl;

			//player velocity *= -1
			Vector2 position = m_a->getComponent<PositionComponent>(1)->getPosition();

			position.x += m_b->getComponent<BehaviourComponent>(3)->getNormalizeVel().x * 3;
			position.y += m_b->getComponent<BehaviourComponent>(3)->getNormalizeVel().y * 3;

			m_a->getComponent<PositionComponent>(1)->setPosition(position);
		}
	}

	void wallCollisionResponse(Entity* m_a, Entity* m_b)
	{
		if (aabbCollision(m_a->getComponent<SpriteComponent>(2)->getRect(),
			m_b->getComponent<SpriteComponent>(2)->getRect()) == true)
		{
			//std::cout << "Wall collision detected" << std::endl;

			//player velocity *= -1
			Vector2 velocity = m_a->getComponent<BehaviourComponent>(3)->getNormalizeVel();
			Vector2 position = m_a->getComponent<PositionComponent>(1)->getPosition();
			//
			velocity.x *= -1;
			velocity.y *= -1;
			//
			position.x += velocity.x * 9;
			position.y += velocity.y * 9;

			m_a->getComponent<PositionComponent>(1)->setPosition(position);
			//m_a->getComponent<BehaviourComponent>(3)->setNormalizeVel(velocity);
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
