//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:18 3 February 2020
// Finished at
// Time taken:
// Known bugs:


#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"

// PositionComponent class deriving from the BaseComponent class,
// since BaseComponent is a template class deriving must be done as shown below
class PositionComponent : public BaseComponent<PositionComponent>
{
public:
	// Default constructor, sets the m_position and the Component's entity ID
	PositionComponent(Vector2 position, int entityID) :
		BaseComponent<PositionComponent>(entityID),
		m_position(position)
	{

	}

	// Returns the current value of the component's m_position
	Vector2 getPosition()
	{
		return m_position;
	}
	// Sets a new value for the component's m_position
	void setPosition(Vector2 position)
	{
		this->m_position = position;
	}

private:
	Vector2 m_position;

};

#endif // !POSITIONCOMPONENT_H