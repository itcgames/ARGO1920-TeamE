//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:06 3 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Game Entity class
class Entity
{
public:
	// Default constructor used for pointers
	Entity()
	{

	}

	// Template class used to get specfic components; derived from the base Component; of  the game 
	// entities, i.e. getComponent<PositionComponent>() accesses the PositionComponent of the entity
	// and aquire it's data
	template <class T>
	T* getComponent(int type)
	{
		return static_cast<T*>(m_component[type]);
	};

	// Template class used to add new components to the entities; provided that these components
	// derive from the base Component
	template <class T>
	void addComponent(Component* component, int type)
	{
		m_component[type] = component;
	};

private:
	std::unordered_map<int, Component*> m_component;
	int m_ID;
};

#endif // !ENTITY_H