//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:11 3 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2.h"

// Component class
class Component
{
public:
	// Virtual used for getting the type, or ID, of the Component type
	virtual int getType() const = 0;
};

// Template class for BaseComponent that derives from the Component,
// acts as template class the allow creation of new Components with easy enough as to
template <class T>
class BaseComponent : public Component
{
public:
	BaseComponent(int id = -1) : m_entityID(id)
	{

	}

	// The entity that this component is attached to through this variable
	int m_entityID;
	// Used for the different type of Component
	static int type;
	int getType() const { return T::type; }
};
static int nextType = 0;
template <typename T> int BaseComponent<T>::type(nextType++);

#endif // !COMPONENT_H