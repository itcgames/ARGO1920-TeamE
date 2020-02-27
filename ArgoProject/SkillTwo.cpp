#include "SkillTwo.h"
SkillTwo::SkillTwo()
{
}

SkillTwo::~SkillTwo()
{
}

void SkillTwo::idle(FSM* fsm)
{
	fsm->setCurrent(new Idle());
	delete this;
}

void SkillTwo::walking(FSM* fsm)
{
	fsm->setCurrent(new Walking());
	delete this;
}