#ifndef IDLE
#define IDLE
#include "FSM.h"
#include "FiniteState.h"
#include "Walking.h"
#include "SkillOne.h"
#include "SkillTwo.h"
#include "SkillThree.h"
#include "SkillFour.h"

class Idle : public FiniteState
{
public:
	Idle();
	~Idle();
	void walking(FSM* fsm);
	void skillOne(FSM* fsm);
	void skillTwo(FSM* fsm);
	void skillThree(FSM* fsm);
	void skillFour(FSM* fsm);
};

#endif