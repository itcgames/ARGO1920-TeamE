
#ifndef BEHAVIOURCOMPONENT_H
#define BEHAVIOURCOMPONENT_H

#include "Component.h"

class BehaviourComponent : public BaseComponent<BehaviourComponent>
{
public:
	BehaviourComponent(Vector2 t_velocity, int t_maxSpeed, int entityID) :
		m_velocity(t_velocity),
		m_maxSpeed(t_maxSpeed),
		BaseComponent<BehaviourComponent>(entityID)
	{

	}

	Vector2 getVelocity()
	{
		return m_velocity;
	}

	void setVelocity(Vector2 t_velocity)
	{
		m_velocity = t_velocity;
	}

	int getMaxSpeed()
	{
		return m_maxSpeed;
	}

	void setMaxSpeed(int t_maxSpeed)
	{
		m_maxSpeed = t_maxSpeed;
	}

private:
	Vector2 m_velocity;
	int m_maxSpeed;
};

#endif // !BEHAVIOURCOMPONENT_H