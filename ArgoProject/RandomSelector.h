#ifndef RANDOMSELECTOR_H
#define RANDOMSELECTOR_H

#include "CompositeNode.h"

class RandomSelector : public CompositeNode   // RandomSelector operates as a Selector, but in a random order instead of from first child to last child.
{
public:
	virtual bool run() override
	{
		for (Node* child : childrenShuffled()) // The order is shuffled
		{
			if (child->run())
			{
				return true;
			}
		}
		return false;
	}
};

#endif // !RANDOMSELECTOR_H
