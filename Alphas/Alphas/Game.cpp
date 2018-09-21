#include "pch.h"
#include "game.h"
#include <iostream>

Game::Game()
{
	//Create the window
	m_window = new sf::RenderWindow(sf::VideoMode(600, 480), "ALPHAS");
	m_camera = new Camera(m_window);

	m_time			= 0.f;
	m_dt			= 1/60.f;
	m_currentTime	= m_masterClock.getElapsedTime().asSeconds();
	m_newTime		= 0.f;
	m_frameTime		= 0.f;
	FPS				= 0;
}


Game::~Game()
{
	delete m_camera;

	delete m_window;
}

void Game::run()
{	
	createPlayer();
	//std::cout << "Total entity: " << m_entityVector.size() << std::endl;

	m_camera->setTarget(m_playerVector[0]);

	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */
	sf::Texture* mapTexture = new sf::Texture;
	if (!mapTexture->loadFromFile("assets/mapa.png"))
	{
		std::cout << "No se ha podido cargar la textura del map" << std::endl;
	}

	sf::Sprite* mapSprite = new sf::Sprite();
	mapSprite->setTexture(*mapTexture);
	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */

	//Run the program while the window is open
	while (m_window->isOpen()){
		m_newTime = m_masterClock.getElapsedTime().asSeconds();
		m_frameTime = m_newTime - m_currentTime;
		m_currentTime = m_newTime;

		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window->close();
		}

		while (m_frameTime > 0.0) {
			float t_deltaTime = std::min(m_frameTime, m_dt);
			/*update(m_time, t_deltaTime);*/
			update();

			m_frameTime -= t_deltaTime;
			m_time += t_deltaTime;
		}

		m_window->clear(sf::Color::Red);

		m_window->draw(*mapSprite);
		draw();

		m_window->display();
	}

	delete mapSprite;
	delete mapTexture;
	deleteAndFree();
}

void Game::update()
{
	m_camera->update();
	for (int i = 0; i < m_entityVector.size(); i++) {
		m_entityVector[i]->update();
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
	Player* player = new Player(m_window);
	m_entityVector.push_back(player);
	m_playerVector.push_back(player);
}
