#include "pch.h"
#include "game.h"
#include "engineManager.h"
#include "camera.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
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
	m_camera->setTarget(m_playerVector[0]);

	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */
	m_engineManager->createMap();
	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */

	createEnemy(200.f, 0.f);
	createEnemy(-200.f, 0.f);
	createEnemy(0.f, 200.f);
	createEnemy(0.f, -200.f);

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
	
	//Update the player/s
	for (int i = 0; i < m_playerVector.size(); i++) {
		m_playerVector[i]->update(p_deltaTime);
	}

	//Update the enemys
	for (int i = 0; i < m_enemyVector.size(); i++) {
		m_enemyVector[i]->update(p_deltaTime);
		
		if (m_enemyVector[i]->isDead()) {
			std::cout << "Enemigo muerto" << std::endl;
			delete m_enemyVector[i];
			m_enemyVector.erase(m_enemyVector.begin() + i);
		}
	}
}


void Game::draw()
{
	//Draw the player/s
	for (int i = 0; i < m_playerVector.size(); i++) {
		m_playerVector[i]->draw();
	}

	//Draw the enemys
	for (int i = 0; i < m_enemyVector.size(); i++) {
		m_enemyVector[i]->draw();
	}
}


void Game::deleteAndFree()
{
	for (int i = 0; i < m_playerVector.size(); i++) {
		delete m_playerVector[i];
		m_playerVector[i] = nullptr;
	}
	for (int i = 0; i < m_enemyVector.size(); i++) {
		delete m_enemyVector[i];
		m_enemyVector[i] = nullptr;
	}
	m_playerVector.clear();
	m_enemyVector.clear();
}


void Game::createPlayer()
{
	Player* player = new Player(0, 0, 100, "assets/spritesheet.png");
	//m_entityVector.push_back(player);
	m_playerVector.push_back(player);
}

void Game::createEnemy(float p_posX, float p_posY)
{
	Enemy* enemy = new Enemy(p_posX, p_posY, 100, "assets/spritesheet.png");
	//m_entityVector.push_back(enemy);
	m_enemyVector.push_back(enemy);
}
