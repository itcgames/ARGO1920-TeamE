#include "SkillTwo.h"
SkillTwo::SkillTwo()
{
}

SkillTwo::~SkillTwo()
{
}

void SkillTwo::idle(FSM* fsm)
{
	//std::cout << "Attack to idle" << std::endl;
	fsm->setCurrent(new Idle());
	delete this;
}

void SkillTwo::walking(FSM* fsm)
{
	//std::cout << "Attack to Walking" << std::endl;
	fsm->setCurrent(new Walking());
	delete this;
}