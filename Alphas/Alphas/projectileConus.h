#pragma once
#include "projectile.h"

class ProjectileStraight;

class ProjectileConus :
	public Projectile
{
public:
	ProjectileConus(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage);
	~ProjectileConus();

	void update(double p_time, double p_deltaTime);

	void draw() override;

private:
	bool	m_deleteOnCollide;
	bool	m_makeInvisible;

	ProjectileStraight*	m_projectile1;
	ProjectileStraight* m_projectile2;
};

