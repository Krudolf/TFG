#pragma once
#include "projectile.h"
class ProjectileStraightSpin :
	public Projectile
{
public:
	ProjectileStraightSpin(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage);
	~ProjectileStraightSpin();

	void update(double p_time, double p_deltaTime);
	void updateStraight(double p_deltaTime);
	void updateSpin();

private:
	bool	m_deleteOnCollide;
	bool	m_straightPhase;
	bool	m_spinPhase;

	float	m_angle;
	float	m_angleStep;
	float	m_spinPositionX;
	float	m_spinPositionY;

	int		m_radius;
};

