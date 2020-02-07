
#ifndef BEHAVIOURSYSTEM_H
#define BEHAVIOURSYSTEM_H

#include <vector>

#include "System.h"
#include "Entity.h"
#include <time.h>

class BehaviourSystem : public System
{
public:
	//
	BehaviourSystem()
	{
	}
	void seek(Vector2 t_targetPosition)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			Vector2 position = Vector2(m_entities[i]->getComponent<PositionComponent>(1)->getPosition());
			m_velocity = t_targetPosition - position;

			Vector2 normalizedVelo = Normalize(m_velocity);// = Vector2(m_entities[i]->getComponent<BehaviourComponent>(3)->getVelocity());
			

			int m_maxSpeed = m_entities[i]->getComponent<BehaviourComponent>(3)->getMaxSpeed();
			position.x += normalizedVelo.x * m_maxSpeed;
			position.y += normalizedVelo.y * m_maxSpeed;

			m_entities[i]->getComponent<PositionComponent>(1)->setPosition(position);
			m_entities[i]->getComponent<BehaviourComponent>(3)->setNormalizeVel(normalizedVelo);
		}
	}

	//This function flees away from a target if the target gets too close
	void flee(Vector2 t_targetPosition)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			Vector2 position = Vector2(m_entities[i]->getComponent<PositionComponent>(1)->getPosition());
			Vector2 direction = t_targetPosition - position;
			float distance = sqrt((direction.x * direction.x) + (direction.y * direction.y));
			std::cout << std::to_string(distance) << std::endl;
			if (distance < 350)
			{
				m_velocity = position - t_targetPosition;
				Vector2 normalizedVelo = Normalize(m_velocity);
				int m_maxSpeed = m_entities[i]->getComponent<BehaviourComponent>(3)->getMaxSpeed();
				position.x += normalizedVelo.x * m_maxSpeed;
				position.y += normalizedVelo.y * m_maxSpeed;
				m_entities[i]->getComponent<PositionComponent>(1)->setPosition(position);
			}
			else
			{
				wander(position);
			}
		}
	}

	void wander(Vector2 t_targetPosition)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			srand(time(NULL));
			Vector2 position = Vector2(m_entities[i]->getComponent<PositionComponent>(1)->getPosition());
			m_velocity = position - t_targetPosition * (rand() % 3) + 1;
			Vector2 normalizedVelo = Normalize(m_velocity);
			int m_maxSpeed = m_entities[i]->getComponent<BehaviourComponent>(3)->getMaxSpeed();
			position.x += normalizedVelo.x * m_maxSpeed;
			position.y += normalizedVelo.y * m_maxSpeed;
			m_entities[i]->getComponent<PositionComponent>(1)->setPosition(position);
		}
	}

	Vector2 Normalize(Vector2& t_vector)
	{
		Vector2 normalizedVector{ 0,0 };
		normalizedVector = t_vector / (sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y)));
		return normalizedVector;
	}

private:
	Vector2 m_velocity;
};

#endif // !BEHAVIOURSYSTEM_H