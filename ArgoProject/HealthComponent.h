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
	HealthComponent(int health, int entityID) :
		m_health(health),
		BaseComponent<HealthComponent>(entityID)
	{

	}

	int getHealth()
	{
		return m_health;
	}

	void setHealth(int health)
	{
		m_health = health;
	}
	
	void addHealth(int health)
	{
		m_health += health;
	}

private:
	int m_health;
};

#endif // !HEALTHCOMPONENT_H