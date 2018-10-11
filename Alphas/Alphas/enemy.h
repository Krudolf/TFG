#pragma once
#include "entity.h"

class Enemy : 
	public Entity
{
public:
	Enemy(float p_posX, float p_posY, float p_velocity, const char* p_path);
	~Enemy();

	void receiveDamage(float p_damage);
	bool isDead() { return m_dead; };

	void update(float p_deltaTime);

private:
	float	m_velocity;
	float	m_health;
	float	m_mana;
	float	m_damage;
	float	m_atackSpeed;
	bool	m_dead;
};