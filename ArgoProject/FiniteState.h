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
		currentState = 0;
	}

	virtual void walking(FSM* a)
	{
		currentState = 1;
	}

	virtual void skillone(FSM* a)
	{
		currentState = 2;
	}

	virtual void skilltwo(FSM* a)
	{
		currentState = 3;
	}

	virtual void skillthree(FSM* a)
	{
		currentState = 4;
	}

	virtual void skillfour(FSM* a)
	{
		currentState = 5;
	}

	virtual void death(FSM* a)
	{
		currentState = 6;
	}
};