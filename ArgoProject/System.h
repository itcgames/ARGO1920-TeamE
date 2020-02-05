//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:12 3 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef BASESYSTEM_H
#define BASESYSTEM_H

#include "Entity.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.h"

// Base System class
class System
{
public:
	// Method used to add new entities into vector of entities used in all systems
	void addEntity(Entity* entity)
	{
		m_entities.push_back(entity);
	}


protected:
	// Vector of entities that will be used in all systems that derive from the base system
	std::vector<Entity*> m_entities;
};

#endif // !BASESYSTEM_H