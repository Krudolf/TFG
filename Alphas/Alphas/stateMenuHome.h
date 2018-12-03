#pragma once
#include "state.h"

class StateMenuHome :
	public State
{
public:
	StateMenuHome();
	~StateMenuHome();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();
};

