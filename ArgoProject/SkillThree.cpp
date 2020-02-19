#include "SkillThree.h"
SkillThree::SkillThree()
{
}

SkillThree::~SkillThree()
{
}

void SkillThree::idle(FSM* fsm)
{
	//std::cout << "Attack to idle" << std::endl;
	fsm->setCurrent(new Idle());
	delete this;
}

void SkillThree::walking(FSM* fsm)
{
	//std::cout << "Attack to Walking" << std::endl;
	fsm->setCurrent(new Walking());
	delete this;
}