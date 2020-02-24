#ifndef ACTIVECOMPONENT_H
#define ACTIVECOMPONENT_H

#include"Component.h"

//
class ActiveComponent : public BaseComponent<ActiveComponent>
{
public:
	ActiveComponent(bool isActive, int entityID) :
		m_isActive(isActive),
		BaseComponent<ActiveComponent>(entityID)
	{

	}

	bool getIsActive()
	{
		return m_isActive;
	}

	void setIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

private:
	bool m_isActive; // Or isAlive
};

#endif // !ACTIVECOMPONENT_H

