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

private:
	Vector2 m_position;

};

#endif // !POSITIONCOMPONENT_H