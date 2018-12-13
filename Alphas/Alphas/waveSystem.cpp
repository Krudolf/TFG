#include "pch.h"
#include "waveSystem.h"
#include "enemy.h"
#include "enemyWarrior.h"
#include "enemyCharger.h"
#include "enemyRanger.h"
#include "enemyBoss.h"
#include "screenGame.h"

#include <cmath>
#include <iostream>


WaveSystem::WaveSystem(std::vector<Point>& p_spawnPoints)
{
	m_waveFactor = 0.8;
	m_wave = 1;
	m_enemyFactor = 4;
	m_enemyAlive = 0;
	m_maxSpawnEnemy = 20;
	m_enemyAlive = 0;
	m_totalEnemyWave = 0;
	m_remainingEnemy = 0;

	m_enemyTypeVector.push_back(EnemyType::WARRIOR);
	m_enemyTypeVector.push_back(EnemyType::CHARGER);
	m_enemyTypeVector.push_back(EnemyType::RANGER);

	m_spawnPointsVector = p_spawnPoints;
}


WaveSystem::~WaveSystem()
{
}


void WaveSystem::createEnemy(EnemyType p_type)
{
	Enemy* t_enemy;
	int t_random = rand() % m_spawnPointsVector.size();

	//Random between -50 and 50 
	float	t_randX = (rand() % 101) - 50;
	float	t_randY = (rand() % 101) - 50;

	Point t_point = m_spawnPointsVector[t_random];
	t_point.x += t_randX;
	t_point.y += t_randY;

	switch (p_type)
	{
		case EnemyType::WARRIOR:
			t_enemy = new EnemyWarrior(t_point.x, t_point.y, "assets/spritesheet.png");
			break;
		case EnemyType::CHARGER:
			t_enemy = new EnemyCharger(t_point.x, t_point.y, "assets/spritesheet.png");
			break;
		case EnemyType::RANGER:
			t_enemy = new EnemyRanger(t_point.x, t_point.y, "assets/spritesheet.png");
			break;
		case EnemyType::BOSS:
			t_enemy = new EnemyBoss(t_point.x, t_point.y, "assets/spritesheet.png");
			break;
	default:
		break;
	}
	//ScreenGame::m_entityVector.push_back(enemy);
	ScreenGame::m_enemyVector.push_back(t_enemy);
}


void WaveSystem::spawnNextWave()
{
	if (m_wave == 1) {
		std::cout << "BOSS SPAWNS!" << std::endl;
		createEnemy(EnemyType::BOSS);
		m_enemyAlive = 1;
		m_remainingEnemy = 0;
	}
	else {
		m_totalEnemyWave = m_wave * m_waveFactor * m_enemyFactor;
		int t_random = 0;
		int t_initialSpawn = 0;

		if (m_totalEnemyWave <= m_maxSpawnEnemy) {
			t_initialSpawn = m_totalEnemyWave;
			m_remainingEnemy = 0;
		}
		else {
			t_initialSpawn = m_maxSpawnEnemy;
			m_remainingEnemy = m_totalEnemyWave - m_maxSpawnEnemy;
		}

		for (int i = 0; i < t_initialSpawn; i++) {
			t_random = rand() % m_enemyTypeVector.size();
			createEnemy(m_enemyTypeVector[t_random]);
		}

		m_enemyAlive = m_totalEnemyWave;
	}
}

void WaveSystem::spawnRemainingEnemy()
{
	int t_random = 0;
	while (m_remainingEnemy > 0 && ScreenGame::m_enemyVector.size() < m_maxSpawnEnemy) {
		t_random = rand() % m_enemyTypeVector.size();
		createEnemy(m_enemyTypeVector[t_random]);

		m_remainingEnemy--;
	}
}

void WaveSystem::checkEndOfWave()
{
	m_enemyAlive--;

	if (m_enemyAlive == 0) {
		m_wave++;
		spawnNextWave();
	}
}