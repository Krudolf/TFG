#pragma once

class State;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void setCurrentState(State* p_newState)		{ m_currentState = p_newState; };
	void setPreviousState(State* p_newState)	{ m_previousState = p_newState; };
	void setGlobalState(State* p_newState)		{ m_globalState = p_newState; };

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();
	void changeState(State* p_newState);
	void goToPreviousState();


private:
	State*	m_currentState;
	State*	m_previousState;
	State*	m_globalState;

};

