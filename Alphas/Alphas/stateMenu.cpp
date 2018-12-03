#include "pch.h"
#include "stateMenu.h"
#include "engineManager.h"
#include "stateMachine.h"


StateMenu::StateMenu() : State()
{
	m_stateMachine = new StateMachine();
	m_stateMachine->setCurrentState(/*TODO: añadir el estado de inicio de menu*/);
}


StateMenu::~StateMenu()
{
}

StateMenu& StateMenu::p()
{
	static StateMenu instance;

	return instance;
}

void StateMenu::init()
{
}

void StateMenu::update(double p_time, double p_deltaTime)
{
}

void StateMenu::draw()
{
	m_engineManager->getWindow()->clear(sf::Color::Green);

	m_engineManager->getWindow()->display();
}

