#include "Idle.h"
Idle::Idle()
{
}


Idle::~Idle()
{
}


void Idle::walking(FSM* fsm)
{
	fsm->setCurrent(new Walking());
	delete this;
}

void Idle::skillOne(FSM* fsm)
{
	fsm->setCurrent(new SkillOne());
	delete this;
}

void Idle::skillTwo(FSM* fsm)
{
	fsm->setCurrent(new SkillTwo());
	delete this;
}

void Idle::skillThree(FSM* fsm)
{
	fsm->setCurrent(new SkillThree());
	delete this;
}

