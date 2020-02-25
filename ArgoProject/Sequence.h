//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:27 24 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "CompositeNode.h"

class Sequence : public CompositeNode 
{
public:
	virtual bool run() override
	{
		for (Node* m_child : getChildren()) // The generic Sequence implementation.
		{
			if (!m_child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
			{
				return false;
			}
		}

		return true;  // All children suceeded, so the entire run() operation succeeds.
	}
};

#endif // !SEQUENCEVEC_H
