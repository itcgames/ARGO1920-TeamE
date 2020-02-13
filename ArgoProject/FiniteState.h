#pragma once
/// @author Aoife Powders
#include "FSM.h"
#include <iostream>

//calls the fsm class
class FSM;
//creates a class state
class FiniteState
{
public:
	int currentState;
	//creates a virtual function
	virtual void idle(FSM* a)
	{
		std::cout << "State Ideling" << std::endl;
		currentState = 0;
	}

	virtual void walking(FSM* a)
	{
		std::cout << "State walking" << std::endl;
		currentState = 1;
	}
};