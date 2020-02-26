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
	CollisionSystem* m_cs;
	int m_maxSpeed;
	float m_enemyHealth;
	float m_rotationAngle;
	bool m_pathfind;
	bool m_seek;
	bool m_attack;
	bool m_collide;
	bool m_attacking;
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
			

		
		}

		return m_status->m_attack;
	}

private:
	PlayerStatus* m_status;
};

#endif // !PLAYERBEHAVIOURS_H