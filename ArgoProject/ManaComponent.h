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
		BaseComponent<ManaComponent>(entityID)
	{

	}

	int getMana()
	{
		return m_mana;
	}

	void setMana(int mana)
	{
		m_mana = mana;
	}

	void addMana(int mana)
	{
		m_mana += mana;
	}

private:
	int m_mana;
};

#endif // !MANACOMPONENT_H