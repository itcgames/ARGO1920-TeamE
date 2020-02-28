//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:37 24 February
// Finished at
// Time taken:
// Known bugs:

#ifndef ENEMYBEHAVIOURS_H
#define ENEMYBEHAVIOURS_H

#include "Node.h"
#include "Vector2.h"

struct EnemyStatus
{
	Vector2 m_position;
	Vector2 m_targetPosition;
	bool m_right;
	bool m_left;
};

//Test behaviour
class MoveLeft : public Node
{
public:
	MoveLeft(EnemyStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		if (m_status->m_left == false)
		{
			if (m_status->m_position.x < 800)
			{
				m_status->m_left = true;
				m_status->m_right = false;
			}
			else
			{
				m_status->m_left = false;
				m_status->m_position.x -= 5;
			}
		}

		return m_status->m_left;
	}



private:
	EnemyStatus* m_status;
	
};

//
class MoveUp : public Node
{
public:
	MoveUp(EnemyStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		m_status->m_position.y -= 5;
		return true;
	}

private:
	EnemyStatus* m_status;

};

//
class MoveDown : public Node
{
public:
	MoveDown(EnemyStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		m_status->m_position.y += 5;
		return true;
	}

private:
	EnemyStatus* m_status;

};

//
class MoveRight : public Node
{
public:
	MoveRight(EnemyStatus* status) :
		m_status(status)
	{

	}

	virtual bool run() override
	{
		if (m_status->m_right == false)
		{
			if (m_status->m_position.x > 1000)
			{
				m_status->m_right = true;
				m_status->m_left = false;
			}
			else
			{
				m_status->m_right = false;
				m_status->m_position.x += 5;
			}
		}

		return m_status->m_right;
	}

private:
	EnemyStatus* m_status;

};
#endif // !ENEMYBEHAVIOURS_H

