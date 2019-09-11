#pragma once
#include "entity.h"

class Player;

class Projectile :
	public Entity
{
public:
	Projectile(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage);
	virtual ~Projectile();

	bool	getReadyToDelete() { return m_readyToDelete; };

	void	update(double p_time, double p_deltaTime);
	void	update();

	void	draw();

	void	setLifeTime(float p_lifeTime);
	void	setReadyToDelete(bool p_readyToDelete) { m_readyToDelete = p_readyToDelete; };

	void	setOwner(Player* p_owner) { m_owner = p_owner; };
	Player*	getOwner() { return m_owner; };

protected:
	Player* m_owner;

	int		m_velocity;
	float	m_moveX;
	float	m_moveY;

	float	m_lifeTime;
	float	m_dieTime;
	float	m_damage;
	
	bool	m_readyToDelete;

	bool	m_crossEnemy;
	bool	m_makeDamage;

	Entities		m_entityOwner;
};

