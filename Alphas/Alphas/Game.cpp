#include "pch.h"
#include "game.h"
#include "engineManager.h"
#include "camera.h"
#include "entity.h"
#include "player.h"
#include <iostream>

Game::Game()
{
	m_engineManager = &EngineManager::p();
	//Create the window
	m_engineManager->createWindow(1280, 720, "ALPHAS");
	m_camera = new Camera();

	m_time			= 0.f;
	m_dt			= 1/60.f;
	m_currentTime	= m_engineManager->getMasterClockSeconds();
	m_newTime		= 0.f;
	m_frameTime		= 0.f;
	FPS				= 0;
}


Game::~Game()
{
	delete m_camera;
}


void Game::run()
{	
	createPlayer();
	//std::cout << "Total entity: " << m_entityVector.size() << std::endl;

	m_camera->setTarget(m_playerVector[0]);

	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */
	m_engineManager->createMap();
	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */

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
		while (m_frameTime > 0.0) {
			float t_deltaTime = std::min(m_frameTime, m_dt);
			update(m_time, t_deltaTime);

			m_frameTime -= t_deltaTime;
			m_time += t_deltaTime;
		}

		m_engineManager->getWindow()->clear(sf::Color::Red);

		m_engineManager->getWindow()->draw(*m_engineManager->getMapSprite());
		draw();

		m_engineManager->getWindow()->display();
	}

	deleteAndFree();
}


void Game::update(double p_time, float p_deltaTime)
{
	m_camera->update();
	for (int i = 0; i < m_entityVector.size(); i++) {
		m_entityVector[i]->update(p_deltaTime);
	}
}


void Game::draw()
{
	for (int i = 0; i < m_entityVector.size(); i++) {
		m_entityVector[i]->draw();
	}
}


void Game::deleteAndFree()
{
	for (int i = 0; i < m_entityVector.size(); i++) {
		delete m_entityVector[i];
		m_entityVector[i] = nullptr;
	}
}


void Game::createPlayer()
{
	Player* player = new Player();
	m_entityVector.push_back(player);
	m_playerVector.push_back(player);
}
