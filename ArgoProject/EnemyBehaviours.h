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
	int currentWaypoint;
	bool m_right;
	bool m_left;

	bool atPoint;
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
				std::cout << "Moving Left" << std::endl;
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
		std::cout << "Moving Up" << std::endl;
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
		std::cout << "Moving Down" << std::endl;
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
				//m_status->m_position.x = 900;
				m_status->m_right = true;
				m_status->m_left = false;
			}
			else
			{
				m_status->m_right = false;
				m_status->m_position.x += 5;
				std::cout << "Moving Right" << std::endl;
			}
		}

		return m_status->m_right;
	}

private:
	EnemyStatus* m_status;

};

class MoveTowards : public Node
{
public:
	MoveTowards(EnemyStatus* status) :
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

		return m_status->m_right;
	}

private:
	EnemyStatus* m_status;

};

#endif // !ENEMYBEHAVIOURS_H

