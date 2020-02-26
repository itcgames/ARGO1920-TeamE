//
// C00204076
// Brandonseah-Dempsey
// Started at 14:32 24 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef ACTION_H
#define ACTION_H

#include "Node.h"

class Action : public Node
{
public:
	Action(const std::string newName, int prob) :
		m_name(newName),
		m_probabilityOfSuccess(prob)
	{

	}

private:
	std::string m_name;
	int m_probabilityOfSuccess;

	virtual bool run() override
	{
		if (std::rand() % 100 < m_probabilityOfSuccess)
		{
			std::cout << m_name << " succeeded." << std::endl;
			return true;
		}
		std::cout << m_name << " failed." << std::endl;
		return false;
	}
};

#endif // !ACTION_H