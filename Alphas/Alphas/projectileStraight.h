#pragma once
#include "projectile.h"
class ProjectileStraight :
	public Projectile
{
public:
	ProjectileStraight(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_entityPosX, float p_entityPosY, float p_damage);
	ProjectileStraight(const char* p_texturePath, Entities p_ent, float p_entityPosX, float p_entityPosY, float p_damage, float p_dirX, float p_dirY);
	~ProjectileStraight();

	void update(double p_time, double p_deltaTime);

private:
	bool	m_deleteOnCollide;


};

