#include "SkillOne.h"

SkillOne::SkillOne()
{
}

SkillOne::~SkillOne()
{
}

void SkillOne::idle(FSM* fsm)
{
	fsm->setCurrent(new Idle());
	delete this;
}

void SkillOne::walking(FSM* fsm)
{
	fsm->setCurrent(new Walking());
	delete this;
}
