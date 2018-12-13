#pragma once
#include "enemy.h"

class Projectile;

class EnemyBoss :
	public Enemy
{
public:
	EnemyBoss(float p_posX, float p_posY, const char* p_path);
	~EnemyBoss();

	void atack();

	void updateAtack();
	void draw() override;

private:
	bool	m_projectileLaunched;

	Projectile*	m_projectile;
};

