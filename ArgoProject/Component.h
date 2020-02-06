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

//
class Component
{
public:
	//
	virtual int getType() const = 0;
};

//
template <class T>
class BaseComponent : public Component
{
public:

	BaseComponent(int id = -1) : m_entityID(id)
	{

	}


	//the entity this component is attached to
	int m_entityID;
	static int type;
	int getType() const { return T::type; }
};
static int nextType = 0;
template <typename T> int BaseComponent<T>::type(nextType++);

#endif // !COMPONENT_H