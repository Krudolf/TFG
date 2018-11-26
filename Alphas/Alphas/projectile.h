#pragma once
#include "entity.h"
class Projectile :
	public Entity
{
public:
	Projectile(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage);
	virtual ~Projectile();

	bool getReadyToDelete() { return m_readyToDelete; };

	void update(double p_time, double p_deltaTime);
	void update(bool p_deleteOnCollide);

	void draw();

protected:
	int		m_velocity;
	float	m_moveX;
	float	m_moveY;

	float	m_lifeTime;
	float	m_dieTime;
	float	m_damage;
	
	bool	m_readyToDelete;

private:

};

