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

	virtual void skillone(FSM* a)
	{
		std::cout << "State Attacking with skill one" << std::endl;
		currentState = 2;
	}

	virtual void skilltwo(FSM* a)
	{
		std::cout << "State Attacking with skill two" << std::endl;
		currentState = 3;
	}

	virtual void skillthree(FSM* a)
	{
		std::cout << "State Attacking with skill three" << std::endl;
		currentState = 4;
	}

	virtual void skillfour(FSM* a)
	{
		std::cout << "State Attacking with skill four" << std::endl;
		currentState = 5;
	}

	virtual void death(FSM* a)
	{
		std::cout << "State Death" << std::endl;
		currentState = 6;
	}
};