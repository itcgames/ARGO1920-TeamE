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

struct EnemyStatus
{
	bool m_isActive;
};

//Test behaviour
class Move : public Node
{
public:
	Move()
	{

	}

	virtual bool run() override
	{
		//Take in entity from ecs and move it 
	}

private:

};

#endif // !ENEMYBEHAVIOURS_H

