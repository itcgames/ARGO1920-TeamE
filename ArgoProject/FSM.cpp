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
