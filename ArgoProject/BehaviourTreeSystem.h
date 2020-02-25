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

		m_left = new MoveLeft(m_enemyStatus);
		m_down = new MoveDown(m_enemyStatus);
		m_up = new MoveUp(m_enemyStatus);
		m_right = new MoveRight(m_enemyStatus);

		m_root->addChild(m_selector);

		//m_selector->addChild(m_right);
		m_selector->addChild(m_sequence);

		m_sequence->addChild(m_left);
		//m_sequence->addChild(m_down);
		m_sequence->addChild(m_right);
		//m_sequence->addChild(m_up);*/
	}

	void run(Entity* entity)
	{
		m_enemyStatus->m_position = entity->getComponent<PositionComponent>(1)->getPosition();

		m_root->run();

		entity->getComponent<PositionComponent>(1)->setPosition(m_enemyStatus->m_position);
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
};

#endif // !BEHAVIOURTREESYSTEM_H