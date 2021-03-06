//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:03 4 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef STAMINACOMPONENT_H
#define STAMINACOMPONENT_H

#include "Component.h"

class StaminaComponent : public BaseComponent<StaminaComponent>
{
public:
	StaminaComponent(int stamina, int entityID) : 
		m_stamina(stamina),
		BaseComponent<StaminaComponent>(entityID)
	{

	}

	int getStamina()
	{
		return m_stamina;
	}

	void setStamina(int stamina)
	{
		m_stamina = stamina;
	}

	void addStamina(int stamina)
	{
		m_stamina += stamina;
	}

private:
	int m_stamina;
};

#endif // !STAMINACOMPONENT_H
