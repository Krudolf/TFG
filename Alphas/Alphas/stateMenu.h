#pragma once
#include "state.h"

class StateMenu :
	public State
{
public:
	~StateMenu();
	static StateMenu& p();

	virtual void init();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

private:
	StateMenu();
};

