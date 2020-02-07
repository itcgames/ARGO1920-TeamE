
#ifndef BEHAVIOURCOMPONENT_H
#define BEHAVIOURCOMPONENT_H

#include "Component.h"

class BehaviourComponent : public BaseComponent<BehaviourComponent>
{
public:
	BehaviourComponent(Vector2 t_velocity, int t_maxSpeed, float t_angle, int entityID) :
		m_velocity(t_velocity),
		m_maxSpeed(t_maxSpeed),
		m_angle(t_angle),
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

	Vector2 getNormalizeVel()
	{
		return m_normalizedVel;
	}

	void setNormalizeVel(Vector2 velocity)
	{
		m_normalizedVel = velocity;
	}

	int getRotationAngle()
	{
		return m_angle;
	}

	void setRotationAngle(int t_angle)
	{
		m_angle = t_angle;
	}

private:
	Vector2 m_velocity, m_normalizedVel;
	int m_maxSpeed;
	float m_angle;
};

#endif // !BEHAVIOURCOMPONENT_H