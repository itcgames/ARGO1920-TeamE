//
// C00204076
// Brandon Seah-Dempsey
// Started at 1:00 4 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"

//
class HealthComponent : public BaseComponent<HealthComponent>
{
public:
	HealthComponent(float health, int entityID) :
		m_health(health),
		m_originalHealth(health),
		BaseComponent<HealthComponent>(entityID)
	{

	}

	float getHealth()
	{
		return m_health;
	}

	float getOriginalHealth()
	{
		return m_originalHealth;
	}

	void setHealth(int health)
	{
		m_health = health;
	}

	void alterHealth(float t_change)
	{
		m_health += t_change;

		if (m_health < 0)
		{
			m_health = 0;
		}
		else if (m_health > m_originalHealth * 2)
		{
			m_health = m_originalHealth * 2;
		}
	}

private:
	float m_health;
	float m_originalHealth;
};

#endif // !HEALTHCOMPONENT_H