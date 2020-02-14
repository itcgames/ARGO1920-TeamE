#pragma once
#include "FSM.h"
#include "FiniteState.h"
#include "Walking.h"
#include "Idle.h"
class SkillFour : public FiniteState
{
public:
	SkillFour();
	~SkillFour();
	void idle(FSM* fsm);
	void walking(FSM* fsm);
};

