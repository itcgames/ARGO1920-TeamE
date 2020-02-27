#include "Walking.h"

Walking::Walking()
{
}


Walking::~Walking()
{
}

void Walking::idle(FSM* fsm)
{
	fsm->setCurrent(new Idle());
	delete this;
}
