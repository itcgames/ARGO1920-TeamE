#ifndef FSM_H
#define FSM_H
#include <iostream>
#include <chrono>
#include <thread>

#include "Idle.h"

class FiniteState;
class FSM
{
	class FiniteState* current;

public:
	FSM();

	int getCurrentState();
	//sets current state
	void setCurrent(FiniteState* s)
	{
		current = s;
	}

	void idle();
	void walking();
	void skillone();
	void skilltwo();
	void skillthree();
	void skillfour();
	void death();
};

#endif