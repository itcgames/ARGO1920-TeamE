#pragma once
#include "FSM.h"
#include "FiniteState.h"
#include "Walking.h"
#include "Idle.h"
class SkillThree : public FiniteState
{
public:
	SkillThree();
	~SkillThree();
	void idle(FSM* fsm);
	void walking(FSM* fsm);
};

