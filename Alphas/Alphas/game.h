#pragma once

#include <vector>

class EngineManager;
class StateMachine;
class State;

class Game
{
public:
	Game();
	~Game();

	void initGameMap();
	void run();
	void update(double p_time, double p_deltaTime);
	void draw();
	
private:
	EngineManager*	m_engineManager;
	
	StateMachine*	m_stateMachine;

	double m_time;
	double m_dt;
	double m_currentTime;
	double m_accumulator;
	float m_newTime;
	float m_frameTime;
	int FPS;
};

