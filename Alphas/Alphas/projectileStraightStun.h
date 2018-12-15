#pragma once
#include "projectile.h"

class ProjectileStraightStun :
	public Projectile
{
public:
	ProjectileStraightStun(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_entityPosX, float p_entityPosY, float p_damage, bool p_crossEnemy, bool p_makeDamage);
	~ProjectileStraightStun();

	void update(double p_time, double p_deltaTime);

private:
	Direction	m_direction;
};

