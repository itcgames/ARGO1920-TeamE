#pragma once
#include "FSM.h"
#include "FiniteState.h"
#include "Walking.h"

class Idle : public FiniteState
{
public:
	Idle();
	~Idle();
	void walking(FSM* fsm);
};

