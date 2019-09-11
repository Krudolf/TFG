#include "pch.h"
#include "state.h"
#include "engineManager.h"


State::State()
{
	m_engineManager = &EngineManager::p();
}


State::~State()
{
}

State& State::p()
{
	static State instance;
	return instance;
}

void State::init()
{
}

void State::update(double p_time, double p_deltaTime)
{
}

void State::draw()
{
}
