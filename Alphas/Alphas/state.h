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

	//virtual void init() = 0;
	//virtual void update(double p_time, double p_deltaTime) = 0;
	//virtual void draw() = 0;

protected:
	State();

	EngineManager* m_engineManager;

};

