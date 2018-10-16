#pragma once
#include "entity.h"
class Projectile :
	public Entity
{
public:
	Projectile(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage);
	~Projectile();

	bool getReadyToDelete() { return m_readyToDelete; };

	void update(float p_deltaTime);

private:
	int		m_velocity = 300;
	int		m_moveX;
	int		m_moveY;

	float	m_damage;

	float	m_lifeTime;
	float	m_dieTime;
	bool	m_readyToDelete;
};

