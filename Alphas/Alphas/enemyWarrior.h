#pragma once
#include "enemy.h"

class EnemyWarrior :
	public Enemy
{
public:
	EnemyWarrior(float p_posX, float p_posY, const char* p_path);
	~EnemyWarrior();

	void atack();

	void updateAtack();
};

