//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:12 3 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef BASESYSTEM_H
#define BASESYSTEM_H

#include "ECS.h"
#include "Entity.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.h"

//
class System
{
public:
	void addEntity(Entity* entity)
	{
		m_entities.push_back(entity);
	}

	void deleteEntity(Entity* entity)
	{
		//Checks through all elements of vector
		for (int i = 0; i < m_entities.size(); i++)
		{
			// If vector equals to entity you want to delete...
			if (m_entities[i] == entity)
			{
				// ...and that entity's ActiveComponent iAlive is false..
				if (m_entities[i]->getComponent<ActiveComponent>(6)->getIsActive() == false)
				{
					m_entities[i] = nullptr;
					// ...that entity is erased
					m_entities.erase(m_entities.begin() + i);
					break;
				}
			}
		}
	}

	int getEntitiesSize()
	{
		return m_entities.size();
	}


protected:
	std::vector<Entity*> m_entities;
};

#endif // !BASESYSTEM_H