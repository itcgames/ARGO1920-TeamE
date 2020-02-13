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

void Idle::skillOne(FSM* fsm)
{
	std::cout << "idle to attack" << std::endl;
	fsm->setCurrent(new SkillOne());
	delete this;
}

void Idle::skillTwo(FSM* fsm)
{
	std::cout << "idle to attack" << std::endl;
	fsm->setCurrent(new SkillTwo());
	delete this;
}

void Idle::skillThree(FSM* fsm)
{
	std::cout << "idle to attack" << std::endl;
	fsm->setCurrent(new SkillThree());
	delete this;
}

void Idle::skillFour(FSM* fsm)
{
	std::cout << "idle to attack" << std::endl;
	fsm->setCurrent(new SkillFour());
	delete this;
}
