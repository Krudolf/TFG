#include "pch.h"
#include "screenGame.h"
#include "engineManager.h"
#include "screenManager.h"

#include "camera.h"
#include "entity.h"
#include "player.h"
#include "playerBlue.h"
#include "playerGreen.h"
#include "playerYellow.h"
#include "enemy.h"
#include "enemyWarrior.h"
#include "enemyCharger.h"
#include "enemyRanger.h"
#include "potion.h"
#include "potionHealth.h"
#include "potionMana.h"
#include "potionSpeed.h"
#include "potionDamage.h"
#include "potionArmor.h"
#include "potionAtackSpeed.h"
#include "quadTree.h"
#include "tile.h"
#include "sceneMap.h"
#include "interface.h"
#include "waveSystem.h"

#include "screenMenuHome.h"
#include "screenGameOver.h"
#include "screenPause.h"

#include <iostream>

ScreenGame::ScreenGame(Entities p_playerEntity) : Screen()
{
	m_playerEntity = p_playerEntity;

	m_gamePause			= false;
	m_gameOver			= false;

	/* ++++++++++++++++++++++++++ MAP ++++++++++++++++++++++++++ */
	m_sceneMap = new SceneMap("assets/map/tiledMap.tmx", "assets/tiles.png");
	//m_sceneMap = new SceneMap("assets/map/map2.tmx", "assets/map2.png");
	m_quadTree = new QuadTree(0, sf::FloatRect(0, 0, m_sceneMap->getWidth(), m_sceneMap->getHeight()));

	float t_width = m_sceneMap->getWidth();
	float t_height = m_sceneMap->getHeight();
	m_spawnPointsVector.push_back({ 0.f, 0.f });
	m_spawnPointsVector.push_back({ 0.f, t_height });
	m_spawnPointsVector.push_back({ t_width, 0.f });
	m_spawnPointsVector.push_back({ t_width, t_height });
	/* ++++++++++++++++++++++++++ PLAYER ++++++++++++++++++++++++++ */
	Player* t_player;
	switch (p_playerEntity)
	{
		case Entities::PLAYER_BLUE:
			t_player = new PlayerBlue(t_width / 2, t_height / 2, "assets/spritesheet.png");
			break;
		case Entities::PLAYER_GREEN:
			t_player = new PlayerGreen(t_width / 2, t_height / 2, "assets/spritesheet.png");
			break;
		case Entities::PLAYER_YELLOW:
			t_player = new PlayerYellow(t_width / 2, t_height / 2, "assets/spritesheet.png");
			break;
		}
	m_playerVector.push_back(t_player);

	/* ++++++++++++++++++++++++++ CAMERA ++++++++++++++++++++++++++ */
	m_camera = new Camera();
	m_camera->setTarget(m_playerVector[0]);

	/* ++++++++++++++++++++++++++ ENEMY ++++++++++++++++++++++++++ */
	m_waveSystem = new WaveSystem(m_spawnPointsVector);
	//m_waveSystem->setWavenumber(10);
	m_waveSystem->spawnNextWave();
	
	m_interface = new Interface(m_playerVector[0], nullptr, m_waveSystem);
}


ScreenGame::~ScreenGame() 
{
	deleteAndFree();

	delete m_camera;
	m_camera = nullptr;

	delete m_sceneMap;
	m_sceneMap = nullptr;
	
	delete m_quadTree;
	m_quadTree = nullptr;
	
	delete m_waveSystem;
	m_waveSystem = nullptr;
	
	delete m_interface;
	m_interface = nullptr;
}

void ScreenGame::deleteAndFree()
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
	m_tileCollisionVector.clear();
}

void ScreenGame::init()
{

}

void ScreenGame::update(double p_time, double p_deltaTime)
{
	if (!m_gamePause && !m_gameOver) {
		m_camera->update();

		/* QUADTREE */
		m_quadTree->clear();

		for (Entity* t_tile : m_tileCollisionVector) {
			m_quadTree->insert(t_tile);
		}

		std::vector<Entity*> t_returnObjects;
		for (auto t_player : m_playerVector) {
			t_returnObjects.clear();
			m_quadTree->retrieve(t_returnObjects, t_player);
			std::cout << t_returnObjects.size() << std::endl;
		}

		/* ++++++++++++++++++++++++++ UPDATE PLAYER ++++++++++++++++++++++++++ */
		for (int i = 0; i < m_playerVector.size(); i++) {
			m_playerVector[i]->update(p_time, p_deltaTime);
		}
		checkGameOver();

		/* ++++++++++++++++++++++++++ UPDATE ENEMY ++++++++++++++++++++++++++ */
		for (int i = 0; i < m_enemyVector.size(); i++) {
			m_enemyVector[i]->update(p_time, p_deltaTime);

			if (m_enemyVector[i]->isDead()) {
				float t_random = rand() % 101;	//random between 0 and 100;

				if (t_random < 10) {
					Potion* t_potion;
					if (t_random < 3) {
						t_potion = new PotionHealth("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::HEALTH);
					}
					else if (t_random >= 3 && t_random < 6) {
						t_potion = new PotionMana("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::MANA);
					}
					else if (t_random >= 6 && t_random < 7) {
						t_potion = new PotionSpeed("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::SPEED);
					}
					else if (t_random >= 7 && t_random < 8) {
						t_potion = new PotionDamage("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::DAMAGE);
					}
					else if (t_random >= 8 && t_random < 9) {
						t_potion = new PotionArmor("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::ARMOR);
					}
					else if (t_random >= 9 && t_random < 10) {
						t_potion = new PotionAtackSpeed("assets/spritesheet.png", m_enemyVector[i]->getPositionX(), m_enemyVector[i]->getPositionY(), PotionType::ATACK_SPEED);
					}
					m_potionVector.push_back(t_potion);
				}

				delete m_enemyVector[i];
				m_enemyVector[i] = nullptr;
				m_enemyVector.erase(m_enemyVector.begin() + i);
			}
		}
		checkCollisionBetweenEnemys();
		m_waveSystem->spawnRemainingEnemy();
		m_waveSystem->checkEndOfWave();

		/* ++++++++++++++++++++++++++ UPDATE POTION ++++++++++++++++++++++++++ */
		for (int i = 0; i < m_potionVector.size(); i++) {
			m_potionVector[i]->update();
			if (m_potionVector[i]->getEffectUsed()) {
				delete m_potionVector[i];
				m_potionVector[i] = nullptr;
				m_potionVector.erase(m_potionVector.begin() + i);
			}
		}

		/*	INTERFACE */
		m_interface->update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_engineManager->getKeyReleased()) {
			m_engineManager->setKeyReleased(false);
			m_screenManager->setOverlayScreen(new ScreenPause());
			//m_engineManager->pauseClock();
		}
	}
	else if(m_gameOver){
		//GAME OVEEEEER!!
		m_screenManager->setOverlayScreen(new ScreenGameOver(m_playerEntity));
	}
	else if (m_gamePause) {
		//PAUSEEE!!
		m_gamePause = m_screenManager->overlayOpened();
	}
}

void ScreenGame::draw()
{
	m_engineManager->useGameView();

	//Draw the map
	m_sceneMap->draw();
	m_quadTree->debug();

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

	m_engineManager->useInterfaceView();
	m_interface->draw();
}

/*
	Return true if game is cooperative (more than one player).
	Return false if only one player is playing.
*/
bool ScreenGame::getCooperativeMode()
{
	if (m_playerVector.size() == 1)
		return false;
	else if (m_playerVector.size() == 2)
		return true;
}

void ScreenGame::checkGameOver()
{
	if (getCooperativeMode) {
		if (!m_playerVector[0]->getAlive())
			m_gameOver = true;
	}
	else {
		if (!m_playerVector[0]->getAlive() && !m_playerVector[1]->getAlive())
			m_gameOver = true;
	}
}

void ScreenGame::checkCollisionBetweenEnemys()
{
	for (auto t_enemy1 : m_enemyVector) {
		for (auto t_enemy2 : m_enemyVector) {
			if (t_enemy1 != t_enemy2) {
				bool t_collision = m_engineManager->checkCollision(t_enemy1->getSpriteID(), t_enemy2->getSpriteID());
				if (t_collision && t_enemy1->getDistanceToObjective() < t_enemy2->getDistanceToObjective())
					t_enemy2->moveBackwards();
				else if (t_collision && t_enemy2->getDistanceToObjective() < t_enemy1->getDistanceToObjective())
					t_enemy1->moveBackwards();
			}
		}
	}
}


