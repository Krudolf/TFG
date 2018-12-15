#pragma once
#include "projectile.h"

class Player;

class ProjectileSpin :
	public Projectile
{
public:
	ProjectileSpin(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_damage, Player* p_owner);
	~ProjectileSpin();

	void update(double p_time, double p_deltaTime);

private:
	float	m_angle;
	float	m_angleStep;

	int		m_radius;

	Player* m_owner;
};

