#pragma once
#include "projectile.h"
class ProjectileStraight :
	public Projectile
{
public:
	ProjectileStraight(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage);
	~ProjectileStraight();

	void update(double p_time, double p_deltaTime);

private:
	bool	m_deleteOnCollide;


};

