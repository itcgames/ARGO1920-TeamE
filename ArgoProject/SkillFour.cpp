#include "SkillFour.h"
SkillFour::SkillFour()
{
}

SkillFour::~SkillFour()
{
}

void SkillFour::idle(FSM* fsm)
{
	std::cout << "Attack to idle" << std::endl;
	fsm->setCurrent(new Idle());
	delete this;
}

void SkillFour::walking(FSM* fsm)
{
	std::cout << "Attack to Walking" << std::endl;
	fsm->setCurrent(new Walking());
	delete this;
}