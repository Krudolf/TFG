#pragma once
#include "enemyType_enum.h"
#include "Point.h"

#include <vector>

class WaveSystem
{
public:
	WaveSystem(std::vector<Point>& p_spawnPoints);
	~WaveSystem();

	void createEnemy(EnemyType p_type);

	void spawnNextWave();
	void spawnRemainingEnemy();
	void checkEndOfWave();

	int	getWaveNumber() { return m_wave; };
	int	getAliveEnemy() { return m_enemyAlive; };

	void setWavenumber(int p_wave) { m_wave = p_wave; };

private:
	std::vector<EnemyType>	m_enemyTypeVector;
	std::vector<Point>		m_spawnPointsVector;

	float	m_waveFactor;
	
	int		m_wave;
	int		m_enemyFactor;
	int		m_maxSpawnEnemy;	//Cap of enemy spawned at the same time
	int		m_enemyAlive;		//enemy that remain alive
	int		m_totalEnemyWave;	//Number os enemy to spawn in that wave
	int		m_remainingEnemy;	//enemy remaining to spawn
};
