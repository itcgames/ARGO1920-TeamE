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

//
class StatsComponent : public BaseComponent<StatsComponent>
{
public:

	StatsComponent(std::string t_class, int t_health, int t_strength,
		int t_speed, int t_gold, int t_killCount, int entityID) :
		m_class(t_class),
		m_health(t_health),
		m_strength(t_strength),
		m_speed(t_speed),
		m_gold(t_gold),
		m_killCount(t_killCount),
		BaseComponent<StatsComponent>(entityID)
	{

	}

	// Get Methods
	//
	std::string getClass()
	{
		return m_class;
	}

	int getHealth()
	{
		return m_health;
	}


	int getSpeed()
	{
		return m_speed;
	}

	int getGold()
	{
		return m_gold;
	}

	int getkillCount()
	{
		return m_killCount;
	}
	//

	// Set Methods
	//
	void setClass(std::string t_class)
	{
		m_class = t_class;
	}

	void setHealth(int t_health)
	{
		m_health = t_health;
	}

	void setStrength(int t_strength)
	{
		m_strength = t_strength;
	}

	void setSpeed(int t_speed)
	{
		m_speed = t_speed;
	}

	void setGold(int t_gold)
	{
		m_gold = t_gold;
	}

	void setKillCount(int t_killCount)
	{
		m_killCount = t_killCount;

	}

	void alterHealth(int t_change)
	{
		m_health += t_change;
	}

	void addGold(int gold)
	{
		m_gold += gold;
	}

	//

private:
	std::string m_class;

	int m_health; // Physical power
	int m_strength; // Magic power
	int m_speed; // Critical rate
	int m_gold; // HP and defense
	int m_killCount; // Speed
};

#endif // !STATSCOMPONENT_H