#pragma once
#include "projectile.h"

class Enemy;
class Player;

class ProjectileStraightSticky :
	public Projectile
{
public:
	ProjectileStraightSticky(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_entityPosX, float p_entityPosY, float p_damage);
	~ProjectileStraightSticky();

	void update(double p_time, double p_deltaTime);
	void updateStraight(double p_deltaTime);
	void updateSpin();

private:
	Enemy*	m_enemySticky;
	Player* m_playerSticky;

	bool	m_straightPhase;

	float	m_angle;
	float	m_angleStep;

	int		m_radius;
};

