#pragma once
#include "FSM.h"
#include "FiniteState.h"
#include "Walking.h"
#include "Idle.h"
class SkillTwo : public FiniteState
{
public:
	SkillTwo();
	~SkillTwo();
	void idle(FSM* fsm);
	void walking(FSM* fsm);
};

