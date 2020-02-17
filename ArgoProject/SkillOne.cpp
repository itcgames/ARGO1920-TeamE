#include "SkillOne.h"

SkillOne::SkillOne()
{
}

SkillOne::~SkillOne()
{
}

void SkillOne::idle(FSM* fsm)
{
	//std::cout << "Attack to idle" << std::endl;
	fsm->setCurrent(new Idle());
	delete this;
}

void SkillOne::walking(FSM* fsm)
{
	//std::cout << "Attack to Walking" << std::endl;
	fsm->setCurrent(new Walking());
	delete this;
}
