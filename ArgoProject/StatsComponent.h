//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:23 4 February 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef STATSCOMPONENT_H
#define STATSCOMPONENT_H

#include "Component.h"

// StatsComponent class deriving from the BaseComponent class,
// since BaseComponent is a template class deriving must be done as shown below
class StatsComponent : BaseComponent<StatsComponent>
{
public:
	StatsComponent(std::string _class, int strength, int intelligence, 
				   int dexterity, int constitution, int agility, int entityID) :
		m_class(_class),
		m_strength(strength),
		m_intelligence(intelligence),
		m_dexterity(dexterity),
		m_constitution(constitution),
		m_agility(agility),
		BaseComponent<StatsComponent>(entityID)
	{

	}

	// Get Methods
	//
	std::string getClass()
	{
		return m_class;
	}

	int getStrength()
	{
		return m_strength;
	}

	int getIntelligence()
	{
		return m_intelligence;
	}

	int getDexterity()
	{
		return m_dexterity;
	}

	int getConstitution()
	{
		return m_constitution;
	}

	int getAgility()
	{
		return m_agility;
	}
	//

	// Set Methods
	//
	void setClass(std::string _class)
	{
		m_class = _class;
	}

	void setStrength(int strength)
	{
		m_strength = strength;
	}

	void setIntelligence(int intelligence)
	{
		m_intelligence = intelligence;
	}

	void setDexterity(int dexterity)
	{
		m_dexterity = dexterity;
	}

	void setConstitution(int constitution)
	{
		m_constitution = constitution;
	}

	void setAgility(int agility)
	{
		m_agility = agility;
	}
	//

private:
	std::string m_class;

	int m_strength; // Physical power
	int m_intelligence; // Magic power
	int m_dexterity; // Critical rate
	int m_constitution; // HP and defense
	int m_agility; // Speed
};

#endif // !STATSCOMPONENT_H