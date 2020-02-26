//
// C00204076
// BrandonSeah-Dempsey
// Started at 15:17 24 February 2020
// Finished at 
// Time taken:
// Known bugs:

#ifndef BEHAVIOURTREESYSTEM_H
#define BEHAVIOURTREESYSTEM_H

#include <vector>

#include "System.h"
#include "Entity.h"

#include "Node.h"
#include "CompositeNode.h"
#include "Selector.h"
#include "Sequence.h"
//#include "Root.h"

#include "EnemyBehaviours.h"


class BehaviourTreeSystem : public System
{
public:
	BehaviourTreeSystem()
	{
		m_enemyStatus = new EnemyStatus{ Vector2(0,0), true, false };

		m_selector = new Selector();
		m_sequence = new Sequence();
		m_root = new Sequence();

		m_enemyStatus->currentWaypoint = 1;

		m_left = new MoveLeft(m_enemyStatus);
		m_down = new MoveDown(m_enemyStatus);
		m_up = new MoveUp(m_enemyStatus);
		m_right = new MoveRight(m_enemyStatus);
		m_towards = new MoveTowards(m_enemyStatus);

		m_root->addChild(m_selector);

		//m_selector->addChild(m_right);
		m_selector->addChild(m_sequence);

		//m_sequence->addChild(m_left);
		//m_sequence->addChild(m_down);
		//m_sequence->addChild(m_right);
		//m_sequence->addChild(m_up);*/
		m_sequence->addChild(m_towards);
	}

	void run(Entity* entity,std::vector<Vector2> waypoints)
	{
		if(m_enemyStatus->m_position != waypoints.back())
		{
			m_enemyStatus->m_position = entity->getComponent<PositionComponent>(1)->getPosition();

			m_enemyStatus->m_targetPosition = waypoints[m_enemyStatus->currentWaypoint];

			m_root->run();

			entity->getComponent<PositionComponent>(1)->setPosition(m_enemyStatus->m_position);

			if (m_enemyStatus->m_position == waypoints[m_enemyStatus->currentWaypoint])
			{
				m_enemyStatus->currentWaypoint++;
			}
		}
	}

private:
	Selector* m_selector;
	Sequence* m_sequence;
	Sequence* m_root;

	EnemyStatus* m_enemyStatus;
	MoveLeft* m_left;
	MoveDown* m_down;
	MoveUp* m_up;
	MoveRight* m_right;
	MoveTowards* m_towards;

};

#endif // !BEHAVIOURTREESYSTEM_H