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

//
class PositionComponent : public BaseComponent<PositionComponent>
{
public:
	PositionComponent(Vector2 position, int entityID) :
		BaseComponent<PositionComponent>(entityID),
		m_position(position)
	{
		m_previousPos = Vector2(0, 0);
	}

	//
	Vector2 getPosition()
	{
		return m_position;
	}
	//
	void setPosition(Vector2 position)
	{
		this->m_position = position;
	}

	//
	Vector2 getPreviousPosition()
	{
		return m_previousPos;
	}
	//
	void setPreviousPosition(Vector2 previous)
	{
		m_previousPos = previous;
	}

private:
	Vector2 m_position;
	Vector2 m_previousPos;

};

#endif // !POSITIONCOMPONENT_H