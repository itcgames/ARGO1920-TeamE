//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:30 24 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef ROOT_H
#define ROOT_H

#include "Node.h"

class Root : public Node
{
public:
	void setChild(Node* newChild)
	{
		m_child = newChild;
	}

	virtual bool run() override
	{
		return m_child->run();
	}

private:
	Node* m_child;
};

#endif // ROOT_H