#include "pch.h"
#include "stateMachine.h"
#include "state.h"

StateMachine::StateMachine()
{
	m_currentState	= nullptr;
	m_previousState = nullptr;
	m_globalState	= nullptr;
}


StateMachine::~StateMachine()
{
}

void StateMachine::init()
{
	m_currentState->init();
}

void StateMachine::update(double p_time, double p_deltaTime)
{
	if (m_globalState)
		m_globalState->update(p_time, p_deltaTime);

	if (m_currentState)
		m_currentState->update(p_time, p_deltaTime);
}

void StateMachine::draw()
{
	m_currentState->draw();
}

void StateMachine::changeState(State* p_newState)
{
	m_previousState = m_currentState;

	m_currentState = p_newState;

	m_currentState->init();
}

void StateMachine::goToPreviousState()
{
	changeState(m_previousState);
}
