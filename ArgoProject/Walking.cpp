#include "Walking.h"

Walking::Walking()
{
}


Walking::~Walking()
{
}

void Walking::idle(FSM* fsm)
{
	//std::cout << "Walking to Ideling" << std::endl;
	fsm->setCurrent(new Idle());
	delete this;
}
