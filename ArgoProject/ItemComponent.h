//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:38 11 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef ITEMCOMPONENT_H
#define ITEMCOMPONENT_H

#include "Component.h"

//
class ItemComponent : public BaseComponent<ItemComponent>
{
public:
	ItemComponent(std::string type, bool isSmall, bool isMedium, bool isLarge, int entityID) :
		m_type(type),
		m_isSmall(isSmall),
		m_isMedium(isMedium),
		m_isLarge(isLarge),
		BaseComponent<ItemComponent>(entityID)
	{
		// If m_type is not set to any appropriate value item defaults to a small
		// healing potion
		if (m_type != "Health" && m_type != "health" && 
			m_type != "Mana" && m_type != "mana" && 
			m_type != "Stamina" && m_type != "stamina" && 
			m_type != "Gold" && m_type != "gold")
		{
			m_type = "Health";
			m_isSmall = true;
			m_isMedium = false;
			m_isLarge = false;
		}
		//
		else
		{
			//
			if (m_isSmall == true)
			{
				m_value = 100;
			}
			//
			else if (m_isMedium == true)
			{
				m_value = 250;
			}
			//
			else if (m_isLarge == true)
			{
				m_value = 500;
			}
		}
	}

	//
	std::string getType()
	{
		return m_type;
	}

	int getValue()
	{
		return m_value;
	}

	//
	void setType(std::string type)
	{
		m_type = type;
	}



private:
	std::string m_type;
	bool m_isSmall, m_isMedium, m_isLarge;
	int m_value;
};

#endif // !ITEMCOMPONENT_H
