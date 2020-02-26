//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:14 Feburary 2020
// Finished at
// Time taken:
// Known bugs:

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <initializer_list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>

class Node // This class represents each node in the behaviour tree.
{
public:
	// Run will be used by all classthe derive from the Node class
	virtual bool run() = 0;
};

#endif // !NODE_H
