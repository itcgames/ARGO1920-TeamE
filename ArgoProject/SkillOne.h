#pragma once
#include "FSM.h"
#include "FiniteState.h"
#include "Walking.h"
#include "Idle.h"

class SkillOne : public FiniteState
{
public:
	SkillOne();
	~SkillOne();
	void idle(FSM* fsm);
	void walking(FSM* fsm);
};

