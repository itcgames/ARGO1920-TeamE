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

//
class System
{
public:
	void addEntity(Entity* entity)
	{
		m_entities.push_back(entity);
		std::cout << "111" << std::endl;
	}


protected:
	std::vector<Entity*> m_entities;
};

#endif // !BASESYSTEM_H