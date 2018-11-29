#include "pch.h"
#include "game.h"
#include "engineManager.h"

#include "stateMachine.h"
#include "state.h"
#include "stateMenu.h"
#include "stateGame.h"

#include <iostream>

Game::Game()
{
	m_engineManager = &EngineManager::p();
	//Create the window
	m_engineManager->createWindow(1280, 720, "ALPHAS");

	m_stateMachine = new StateMachine();
	m_stateMachine->setCurrentState(&StateMenu::p());

	m_time			= 0.f;
	m_dt			= 0.01;
	m_currentTime	= m_engineManager->getMasterClockSeconds();
	m_accumulator	= 0.0;
	m_newTime		= 0.f;
	m_frameTime		= 0.f;
	FPS				= 0;
}


Game::~Game()
{
}


void Game::run()
{	
	//initGameMap();
	m_stateMachine->init();

	//Run the program while the window is open
	while (m_engineManager->getWindow()->isOpen()){
		sf::Event event;
		while (m_engineManager->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_engineManager->getWindow()->close();
		}
		
		m_newTime = m_engineManager->getMasterClockSeconds();
		m_frameTime = m_newTime - m_currentTime;
		m_currentTime = m_newTime;

		m_accumulator += m_frameTime;
		
		while (m_accumulator >= m_dt) {
			//float t_deltaTime = std::min(m_frameTime, m_dt);
			//update(m_time, m_dt);
			m_stateMachine->update(m_time, m_dt);

			m_accumulator -= m_dt;
			m_time += m_dt;
		}

		//draw();
		m_stateMachine->draw();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			m_stateMachine->changeState(&StateGame::p());
	}
}

void Game::update(double p_time, double p_deltaTime)
{
	m_stateMachine->update(p_time, p_deltaTime);
}

void Game::draw()
{
	m_stateMachine->draw();
}

void Game::initGameMap()
{
	m_stateMachine->init();
}
