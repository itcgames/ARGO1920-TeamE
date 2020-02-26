//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:16 24 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "Node.h"

class CompositeNode : public Node   //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
{
public:
	const std::vector<Node*>& getChildren() const
	{
		return m_children;
	}

	void addChild(Node* child)
	{
		m_children.emplace_back(child);
	}

	void addChildren(std::initializer_list<Node*>&& newChildren)
	{
		for (Node* child : newChildren)
		{
			addChild(child);
		}
	}

	template <typename CONTAINER>
	void addChildren(const CONTAINER& newChildren)
	{
		for (Node* child : newChildren)
		{
			addChild(child);
		}
	}

private:
	std::vector<Node*> m_children;

protected:
	std::vector<Node*> childrenShuffled() const
	{
		std::vector<Node*> temp = m_children;
		std::random_shuffle(temp.begin(), temp.end());
		return temp;
	}
};

#endif // !COMPOSITENODE_H