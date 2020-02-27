#include "SkillThree.h"
SkillThree::SkillThree()
{
}

SkillThree::~SkillThree()
{
}

void SkillThree::idle(FSM* fsm)
{
	fsm->setCurrent(new Idle());
	delete this;
}

void SkillThree::walking(FSM* fsm)
{
	fsm->setCurrent(new Walking());
	delete this;
}