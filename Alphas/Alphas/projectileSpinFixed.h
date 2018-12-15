#pragma once
#include "projectile.h"

class ProjectileSpinFixed :
	public Projectile
{
public:
	ProjectileSpinFixed(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage);
	~ProjectileSpinFixed();

	void update(double p_time, double p_deltaTime);

	void draw() override;

private:
	float	m_centerPosX;
	float	m_centerPosY;
	float	m_angle;
	float	m_angleStep;
	float	m_nextCheckTime;


	int		m_radius;
};

