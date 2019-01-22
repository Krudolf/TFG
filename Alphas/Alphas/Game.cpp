#include "pch.h"
#include "game.h"
#include "engineManager.h"

#include "screenManager.h"
#include "screen.h"
#include "screenMenuHome.h"
#include "screenSelectPlayerSolo.h"
#include "screenGame.h"

#include <iostream>

Game::Game()
{
	m_engineManager = &EngineManager::p();
	m_engineManager->createWindow(1280, 720, "ALPHAS");

	m_screenManager = &ScreenManager::p();
	m_screenManager->setCurrentScreen(new ScreenMenuHome());
	m_screenManager->init();

	m_time			= 0.f;
	m_dt			= 1.f/60.f;
	m_currentTime	= m_engineManager->getMasterClockSeconds();
	m_accumulator	= 0.0;
	m_newTime		= 0.f;
	m_elapsedTime	= 0.f;
	FPS				= 0;
}


Game::~Game()
{
}


void Game::run()
{	
	//Run the program while the window is open
	while (m_engineManager->getWindow()->isOpen()){
		m_engineManager->checkEvents();

		m_newTime = m_engineManager->updateMasterClock();
		m_elapsedTime = m_newTime - m_currentTime;
		m_currentTime = m_newTime;

		m_accumulator += m_elapsedTime;
		
		while (m_accumulator >= m_dt) {
			update(m_newTime, m_dt);

			m_accumulator -= m_dt;
		}

		draw();
	}
}

void Game::update(double p_time, double p_deltaTime)
{
	m_screenManager->update(p_time, p_deltaTime);
}

void Game::draw()
{
	m_screenManager->draw();
}

void Game::init()
{
	m_screenManager->init();
}
