//
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
				m_value = 10;
			}
			//
			else if (m_isMedium == true)
			{
				m_value = 20;
			}
			//
			else if (m_isLarge == true)
			{
				m_value = 30;
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

	bool getIsSmall()
	{
		return m_isSmall;
	}

	bool getIsMedium()
	{
		return m_isMedium;
	}

	bool getIsLarge()
	{
		return m_isLarge;
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
