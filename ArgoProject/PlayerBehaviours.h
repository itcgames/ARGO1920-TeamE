//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:19 26 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef PLAYERBEHAVIOURS_H
#define PLAYERBEHAVIOURS_H

#include "Node.h"
#include "Vector2.h"

#include "IEnemy.h"
#include "IPlayer.h"
#include "Entity.h"

#include "CollisionSystem.h"

struct PlayerStatus
{
	Vector2 m_position;
	Vector2 m_targetPosition;
	Vector2 m_normalisedVec;
	Vector2 m_playerWH;
	Vector2 m_targetWH;
	CollisionSystem* m_cs;
	int m_maxSpeed;
	float m_rotationAngle;
	bool m_pathfind;
	bool m_seek;
	bool m_attack;
	bool m_collide;
	int currentWaypoint;
	bool atPoint;


};

class PathFind : public Node
{
public:
	PathFind(PlayerStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		if (m_status->m_pathfind == false)
		{

		}

		return m_status->m_pathfind;
	}

	void findEnemy()
	{

	}

private:
	PlayerStatus* m_status;
};

class Seek : public Node
{
public:
	Seek(PlayerStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		if (m_status->m_seek == false)
		{
			seek();
			collide();
		}

		return m_status->m_seek;
	}

	void seek()
	{
		position = Vector2(m_status->m_position);
		//change this!!!!!!! move to the center
		m_velocity = (m_status->m_targetPosition - Vector2(25, 25)) - position;
		m_orientation = getOrientation(m_velocity);

		normalizedVelo = Normalize(m_velocity);

		int maxSpeed = m_status->m_maxSpeed;
		position.x += normalizedVelo.x * maxSpeed;
		position.y += normalizedVelo.y * maxSpeed;
		//}
		m_status->m_normalisedVec = normalizedVelo;

		m_status->m_rotationAngle = m_orientation * (180 / 3.14159);
		m_status->m_position = position;
	}

	void collide()
	{
		if (m_status->m_position.x + m_status->m_playerWH.x >= m_status->m_targetPosition.x &&
			m_status->m_targetPosition.x + m_status->m_targetWH.x >= m_status->m_position.x &&
			m_status->m_position.y + m_status->m_playerWH.y >= m_status->m_targetPosition.y &&
			m_status->m_targetPosition.y + m_status->m_targetWH.y >= m_status->m_position.y)
		{
			m_status->m_collide = true;
		}
		else
		{
			m_status->m_collide = false;
		}
	}

	Vector2 Normalize(Vector2& t_vector)
	{
		Vector2 normalizedVector{ 0,0 };
		normalizedVector = t_vector / (sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y)));
		return normalizedVector;
	}

	float getOrientation(Vector2& t_vector)
	{
		return atan2(-t_vector.y, -t_vector.x);
	}

private:
	PlayerStatus* m_status;

	Vector2 position;
	Vector2 m_velocity;
	float m_orientation;

	Vector2 normalizedVelo;

	int maxSpeed;
};

class Attack : public Node
{
public:
	Attack(PlayerStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		if (m_status->m_attack == false)
		{
			
			if (m_status->m_position.x + m_status->m_playerWH.x >= m_status->m_targetPosition.x &&
				m_status->m_targetPosition.x + m_status->m_targetWH.x >= m_status->m_position.x &&
				m_status->m_position.y + m_status->m_playerWH.y >= m_status->m_targetPosition.y &&
				m_status->m_targetPosition.y + m_status->m_targetWH.y >= m_status->m_position.y)
			{
				m_status->m_collide = true;
			}
			else
			{
				m_status->m_collide = false;
			}
		}

		return m_status->m_attack;
	}

private:
	PlayerStatus* m_status;
};

class MoveTowards : public Node
{
public:
	MoveTowards(PlayerStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		if (m_status->atPoint == false)
		{
			if (m_status->m_position == m_status->m_targetPosition)
			{
				m_status->atPoint = true;
			}
			else
			{
				//m_status->atPoint = false;
				Vector2 movementVector = m_status->m_targetPosition - m_status->m_position;
				//float distance = sqrt(movementVector.x * movementVector.x + movementVector.y * movementVector.y);
				//Vector2 normalVect = { movementVector.x / distance,movementVector.y / distance };
				//m_status->m_position += normalVect * 2;*/
				if (movementVector.x > 0)
				{
					if (m_status->m_position.x != m_status->m_targetPosition.x)
					{
						m_status->m_position.x += 5;
					}
				}
				else
				{
					if (m_status->m_position.x != m_status->m_targetPosition.x)
					{
						m_status->m_position.x -= 5;
					}
				}

				if (movementVector.y > 0)
				{
					if (m_status->m_position.y != m_status->m_targetPosition.y && m_status->m_position.x == m_status->m_targetPosition.x)
					{
						m_status->m_position.y += 5;
					}
				}
				else
				{
					if (m_status->m_position.y != m_status->m_targetPosition.y && m_status->m_position.x == m_status->m_targetPosition.x)
					{
						m_status->m_position.y -= 5;
					}
				}

				std::cout << "Moving Towards" << std::endl;
			}
		}

		return m_status->atPoint;
	}

private:
	PlayerStatus* m_status;

};

class GetHealth : public Node
{
public:
	GetHealth(PlayerStatus* status) :
		m_status(status)
	{

	}

	//runs to targetPosititon which will be a health pickup
	virtual bool run() override
	{
		if (m_status->atPoint == false)
		{
			if (m_status->m_position == m_status->m_targetPosition)
			{
				m_status->atPoint = true;
			}
			else
			{
				Vector2 movementVector = m_status->m_targetPosition - m_status->m_position;
				if (movementVector.x > 0)
				{
					if (m_status->m_position.x != m_status->m_targetPosition.x)
					{
						m_status->m_position.x += 5;
					}
				}
				else
				{
					if (m_status->m_position.x != m_status->m_targetPosition.x)
					{
						m_status->m_position.x -= 5;
					}
				}

				if (movementVector.y > 0)
				{
					if (m_status->m_position.y != m_status->m_targetPosition.y && m_status->m_position.x == m_status->m_targetPosition.x)
					{
						m_status->m_position.y += 5;
					}
				}
				else
				{
					if (m_status->m_position.y != m_status->m_targetPosition.y && m_status->m_position.x == m_status->m_targetPosition.x)
					{
						m_status->m_position.y -= 5;
					}
				}

				std::cout << "Getting Health" << std::endl;
			}
		}

		return m_status->atPoint;
	}

private:
	PlayerStatus* m_status;

};


#endif // !PLAYERBEHAVIOURS_H