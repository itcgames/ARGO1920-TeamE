#include "Idle.h"
Idle::Idle()
{
}


Idle::~Idle()
{
}


void Idle::walking(FSM* fsm)
{
	std::cout << "Walking" << std::endl;
	fsm->setCurrent(new Walking());
	delete this;
}