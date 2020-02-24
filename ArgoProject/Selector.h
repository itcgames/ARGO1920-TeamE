//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:24 24 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef SELECTOR_H
#define SELECTOR_H

#include "CompositeNode.h"

class Selector : public CompositeNode
{
public:
	virtual bool run() override
	{
		for (Node* child : getChildren())   // The generic Selector implementation
		{
			if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
			{
				return true;
			}
		}
		return false;  // All children failed so the entire run() operation fails.
	}
};

#endif // !SELECTOR_H
