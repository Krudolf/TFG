#pragma once

#include <vector>

class EngineManager;
class ScreenManager;
class Screen;

class Game
{
public:
	Game();
	~Game();

	void init();
	void run();
	void update(double p_time, double p_deltaTime);
	void draw();
	
private:
	EngineManager*	m_engineManager;
	ScreenManager*	m_screenManager;

	double m_time;
	double m_dt;
	double m_currentTime;
	double m_accumulator;
	float m_newTime;
	float m_frameTime;
	int FPS;
};

