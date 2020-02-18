//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:50 4 February 2020
// Finished at
// Time taken:
// Known bugs:


#ifndef MANACOMPONENT_H
#define MANACOMPONENT_H

#include "Component.h"

class ManaComponent : public BaseComponent<ManaComponent>
{
public:
	ManaComponent(int mana, int entityID) :
		m_mana(mana),
		m_originalMana(mana),
		BaseComponent<ManaComponent>(entityID)
	{

	}

	int getMana()
	{
		return m_mana;
	}

	int getOriginalMana()
	{
		return m_originalMana;
	}

	void setMana(int mana)
	{
		m_mana = mana;
	}

	void alterMana(float t_change)
	{
		m_mana += t_change;

		if(m_mana < 0)
		{
			m_mana = 0;
		}
		else if (m_mana > m_originalMana * 2)
		{
		m_mana = m_originalMana * 2;
		}
	}

private:
	float m_mana;
	float m_originalMana;
};

#endif // !MANACOMPONENT_H