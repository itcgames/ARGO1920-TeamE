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

//
class Entity
{
public:
	//
	Entity()
	{

	}

	~Entity()
	{
		delete this;
	}

	//
	template <class T>
	T* getComponent(int type)
	{
		return static_cast<T*>(m_component[type]);
	};

	//
	template <class T>
	void addComponent(Component* component, int type)
	{
		m_component[type] = component;
	};

	int getID() { return m_ID; }

	template <class T>
	void removeComponent(int type)
	{
		m_component.erase(type);
	};
	
private:
	std::unordered_map<int, Component*> m_component;
	int m_ID;
};

#endif // !ENTITY_H