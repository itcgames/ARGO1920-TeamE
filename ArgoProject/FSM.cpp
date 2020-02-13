#include "FSM.h"

//functions defined using polymorphism
FSM::FSM()
{
	current = new Idle();
}

int FSM::getCurrentState()
{
	return current->currentState;
}

void FSM::idle()
{
	current->idle(this);
}

void FSM::walking()
{
	current->walking(this);
}

void FSM::skillone()
{
	current->skillone(this);
}

void FSM::skilltwo()
{
	current->skilltwo(this);
}

void FSM::skillthree()
{
	current->skillthree(this);
}

void FSM::skillfour()
{
	current->skillfour(this);
}

