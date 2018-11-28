#include "pch.h"
#include "game.h"
#include "engineManager.h"
#include "camera.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "enemyWarrior.h"
#include "enemyCharger.h"
#include "enemyRanger.h"
#include "potion.h"
#include "potionHealth.h"
#include "potionMana.h"
#include "potionSpeed.h"
#include "quadTree.h"
#include "tile.h"
#include <iostream>

#include "sceneMap.h"


Game::Game()
{
	m_engineManager = &EngineManager::p();
	//Create the window
	m_engineManager->createWindow(1280, 720, "ALPHAS");
	m_camera = new Camera();

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
	deleteAndFree();

	delete m_sceneMap;
	delete m_camera;
	delete m_quadTree;
}


void Game::run()
{	
	createPlayer();
	m_camera->setTarget(m_playerVector[0]);

	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */
	m_sceneMap = new SceneMap("assets/map/tiledMap.tmx", "assets/tiles.png");
	//m_sceneMap = new SceneMap("assets/map/map2.tmx", "assets/map2.png");
	//m_quadTree = new QuadTree(0, sf::FloatRect(0, 0, m_sceneMap->getWidth(), m_sceneMap->getHeight()));
	std::vector<Entity*> t_returnObjects;

	/* ++++++++++++++++++++++++++ ENEMY ++++++++++++++++++++++++++ */
	createEnemyWarrior(1000.f, 400.f);
	createEnemyWarrior(600.f, 400.f);
	createEnemyCharger(800.f, 600.f);
	createEnemyCharger(800.f, 200.f);
	createEnemyRanger(675.f, 400.f);
	createEnemyRanger(725.f, 400.f);


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
		
		/* QUADTREE */
		/*m_quadTree->clear();

		for (int i = 0; i < m_entityVector.size(); i++) {
			m_quadTree->insert(m_entityVector[i]);
		}

		for (auto t_player : m_playerVector) {
			t_returnObjects.clear();
			m_quadTree->retrieve(t_returnObjects, t_player);
			std::cout << t_returnObjects.size() << std::endl;
			
		}*/
		
		while (m_accumulator >= m_dt) {
			//float t_deltaTime = std::min(m_frameTime, m_dt);
			update(m_time, m_dt);

			m_accumulator -= m_dt;
			m_time += m_dt;
		}

		m_engineManager->getWindow()->clear(sf::Color::Red);

		draw();

		m_engineManager->getWindow()->display();
	}
}


void Game::update(double p_time, double p_deltaTime)
{
	m_camera->update();
	
	//Update player/s
	for (int i = 0; i < m_playerVector.size(); i++) {
		m_playerVector[i]->update(p_time, p_deltaTime);
	}

	//Update enemys
	for (int i = 0; i < m_enemyVector.size(); i++) {
		m_enemyVector[i]->update(p_time, p_deltaTime);
		
		if (m_enemyVector[i]->isDead()) {
			int random = rand() % 101;	//Random between 0 and 100;
			
			Potion* t_potion;
			if(random > 0 && random <= 50){
				t_potion = new PotionHealth("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::HEALTH);
			}
			else if (random > 50 && random <= 75) {
				t_potion = new PotionSpeed("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::SPEED);
			}
			else if (random > 75 && random <= 100) {
				t_potion = new PotionMana("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::MANA);
			}
			m_potionVector.push_back(t_potion);

			delete m_enemyVector[i];
			m_enemyVector[i] = nullptr;
			m_enemyVector.erase(m_enemyVector.begin() + i);
		}
	}
	checkCollisionBetweenEnemys();

	//Update potions
	for (int i = 0; i < m_potionVector.size(); i++) {
		m_potionVector[i]->update();
		if (m_potionVector[i]->getEffectUsed()) {
			delete m_potionVector[i];
			m_potionVector[i] = nullptr;
			m_potionVector.erase(m_potionVector.begin() + i);
		}
	}
}


void Game::draw()
{
	//Draw the map
	m_sceneMap->draw();
	//m_quadTree->debug();

	//Draw player/s
	for (auto t_player : m_playerVector) {
		t_player->draw();
	}

	//Draw enemys
	for (auto t_enemy : m_enemyVector) {
		t_enemy->draw();
	}

	//Draw potions
	for (auto t_potion : m_potionVector) {
		t_potion->draw();
	}
}


void Game::deleteAndFree()
{
	for (auto t_player : m_playerVector) {
		delete t_player;
		t_player = nullptr;
	}
	for (auto t_enemy : m_enemyVector) {
		delete t_enemy;
		t_enemy = nullptr;
	}
	
	for (auto t_potion : m_potionVector) {
		delete t_potion;
		t_potion = nullptr;
	}

	m_playerVector.clear();
	m_enemyVector.clear();
	m_potionVector.clear();
	m_entityVector.clear();
}

bool Game::getCooperativeMode()
{
	if (m_playerVector.size() > 1)
		return true;
	else
		return false;
}

void Game::checkCollisionBetweenEnemys()
{
	for (auto t_enemy1 : m_enemyVector) {
		for (auto t_enemy2 : m_enemyVector) {
			if (t_enemy1 != t_enemy2) {
				bool t_collision = m_engineManager->checkCollision(t_enemy1->getSpriteID(), t_enemy2->getSpriteID());
				if (t_collision && t_enemy1->getDistanceToObjective() < t_enemy2->getDistanceToObjective())
					t_enemy2->moveBackwards();
				else if(t_collision && t_enemy2->getDistanceToObjective() < t_enemy1->getDistanceToObjective())
					t_enemy1->moveBackwards();
			}
		}
	}
}


void Game::createPlayer()
{
	//Player* player = new Player(800, 400, "assets/spritesheet.png");
	Player* player = new Player(0, 0, "assets/spritesheet.png");
	//m_entityVector.push_back(player);
	m_playerVector.push_back(player);
}

void Game::createEnemyWarrior(float p_posX, float p_posY)
{
	EnemyWarrior* enemy = new EnemyWarrior(p_posX, p_posY, "assets/spritesheet.png");
	//m_entityVector.push_back(enemy);
	m_enemyVector.push_back(enemy);
}

void Game::createEnemyCharger(float p_posX, float p_posY)
{
	EnemyCharger* enemy = new EnemyCharger(p_posX, p_posY, "assets/spritesheet.png");
	//m_entityVector.push_back(enemy);
	m_enemyVector.push_back(enemy);
}

void Game::createEnemyRanger(float p_posX, float p_posY)
{
	EnemyRanger* enemy = new EnemyRanger(p_posX, p_posY, "assets/spritesheet.png");
	//m_entityVector.push_back(enemy);
	m_enemyVector.push_back(enemy);
}
