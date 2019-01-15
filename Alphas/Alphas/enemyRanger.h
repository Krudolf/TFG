#pragma once
#include "enemy.h"

class Projectile;

class EnemyRanger :
	public Enemy
{
public:
	EnemyRanger(float p_posX, float p_posY, const char* p_path, int p_waveNumber);
	~EnemyRanger();

	void atack();
	void updateAtack();

	//void update(double p_time, double p_deltaTime);

	void draw() override;

private:
	Projectile* m_projectile;

	bool	m_projectileLaunched;
};

