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
#include "PlayerBehaviours.h"

/*
Example:
		Root
			 |
			 |
  Selector (only one of these children need to succeed)
	   /             \
	  /               \
	 /                 \
Door is open?      Sequence (all of these children need to succeed)
(if door is                /           \
already open,             /             \
we are done)             /               \
				   Approach door      Open the door
				  (if this fails
				  then the door
				  cannot be opened)
*/


class BehaviourTreeSystem : public System
{
public:
	BehaviourTreeSystem()
	{
		initEnemy();
	}

	void initEnemy()
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

		m_selector->addChild(m_sequence);

		m_sequence->addChild(m_left);
		m_sequence->addChild(m_right);
	}

	void initPlayer(Vector2 position, Vector2 targetPosition, Vector2 normalisedVec,
		Vector2 playerWH, Vector2 targetWH, CollisionSystem* cs, int maxSpeed,  
		float rotationAngle, bool pathfind, bool seek, bool attack)
	{
		m_playerStatus = new PlayerStatus{ position, targetPosition, normalisedVec,
			playerWH, targetWH, cs, maxSpeed, rotationAngle, pathfind, seek, attack };


		m_playerStatus->currentWaypoint = 1;

		m_pselector = new Selector();
		m_psequence = new Sequence();
		m_proot = new Sequence();

		m_seek = new Seek(m_playerStatus);
		m_attack = new Attack(m_playerStatus);
		m_towards = new MoveTowards(m_playerStatus);
		m_health = new GetHealth(m_playerStatus);

		m_proot->addChild(m_pselector);
		
		m_pselector->addChild(m_psequence);

		m_psequence->addChild(m_towards);
		m_psequence->addChild(m_health);
		//m_psequence->addChild(m_seek);
		//m_psequence->addChild(m_attack);
	}

	/*void run(Entity* entity)
	{
		m_enemyStatus->m_position = entity->getComponent<PositionComponent>(1)->getPosition();

		m_root->run();

		entity->getComponent<PositionComponent>(1)->setPosition(m_enemyStatus->m_position);
	}*/
	void run(Entity* entity, std::vector<Vector2> waypoints)
	{
		if (m_playerStatus->m_position != waypoints.back())
		{
			m_playerStatus->m_position = entity->getComponent<PositionComponent>(1)->getPosition();

			m_playerStatus->m_targetPosition = waypoints[m_playerStatus->currentWaypoint];

			m_proot->run();

			entity->getComponent<PositionComponent>(1)->setPosition(m_playerStatus->m_position);

			if (m_playerStatus->m_position == waypoints[m_playerStatus->currentWaypoint])
			{
				m_playerStatus->currentWaypoint++;
			}
		}
	}

	void runPlayer(Entity* a, Entity* b)
	{
		m_playerStatus->m_position = a->getComponent<PositionComponent>(1)->getPosition();
		m_playerStatus->m_targetPosition = b->getComponent<PositionComponent>(1)->getPosition();
		m_playerStatus->m_normalisedVec = a->getComponent<BehaviourComponent>(3)->getNormalizeVel();
		m_playerStatus->m_rotationAngle = a->getComponent<BehaviourComponent>(3)->getRotationAngle();

		m_playerStatus->m_playerWH.x = a->getComponent<SpriteComponent>(2)->getRect()->w;
		m_playerStatus->m_playerWH.y = a->getComponent<SpriteComponent>(2)->getRect()->h;
		m_playerStatus->m_targetWH.x = b->getComponent<SpriteComponent>(2)->getRect()->w;
		m_playerStatus->m_targetWH.y = b->getComponent<SpriteComponent>(2)->getRect()->h;


		m_proot->run();

		a->getComponent<PositionComponent>(1)->setPosition(m_playerStatus->m_position);
		a->getComponent<BehaviourComponent>(3)->setNormalizeVel(m_playerStatus->m_normalisedVec);
		a->getComponent<BehaviourComponent>(3)->setRotationAngle(m_playerStatus->m_rotationAngle);
		a->getComponent<BehaviourComponent>(3)->setCollide(m_playerStatus->m_collide);
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

	PlayerStatus* m_playerStatus;
	Selector* m_pselector;
	Sequence* m_psequence;
	Sequence* m_proot;
	//PathFind* m_pathfind;
	Seek* m_seek;
	Attack* m_attack;
	MoveTowards* m_towards;
	GetHealth* m_health;

};

#endif // !BEHAVIOURTREESYSTEM_H