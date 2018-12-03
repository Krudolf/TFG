#pragma once

class EngineManager;

class State
{
public:
	virtual ~State();
	static State& p();

	virtual void init();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

protected:
	State();

	EngineManager* m_engineManager;
};

