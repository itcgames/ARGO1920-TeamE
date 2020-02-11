//
// C00204076
// Brandon Seah-Dempsey
// Started at 11:08 11 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

#include "Component.h"

//
class SkillComponent : public BaseComponent<SkillComponent>
{
public:
	SkillComponent(std::string name, std::string targetType, std::string skillType, 
		int value, int entityID) :
		m_name(name),
		m_targetType(targetType),
		m_skillType(skillType),
		m_value(value),
		BaseComponent<SkillComponent>(entityID)
	{

	}

	// Get Methods
	std::string getName()
	{
		return m_name;
	}

	std::string getTargetType()
	{
		return m_targetType;
	}

	std::string getSkillType()
	{
		return m_skillType;
	}

	int getValue()
	{
		return m_value;
	}

	// Set Methods
	void setName(std::string name)
	{
		m_name = name;
	}

	void setTargetType(std::string targetType)
	{
		m_targetType = targetType;
	}

	void setSkillType(std::string skillType)
	{
		m_skillType = skillType;
	}

	void setValue(int value)
	{
		m_value = value;
	}

private:
	std::string m_name;
	/*
	Self
	Party
	Ally
	Enemy
	All
	*/
	std::string m_targetType;
	/*
	Damage
	Buffing
	Healing
	*/
	std::string m_skillType;

	int m_value;
};

#endif // !SKILLCOMPONENT_H
