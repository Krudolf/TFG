#pragma once
#include "entity.h"

class Player;

class Enemy : 
	public Entity
{
public:
	Enemy(float p_posX, float p_posY, const char* p_path);
	virtual ~Enemy();

	void receiveDamage(float p_damage);
	bool isDead() { return m_dead; };

	double calculateDistance(Player* p_posibleObjective);
	double getDistanceToObjective() { return m_distanceToObjective; };
	
	void checkObjective();
	void move();
	virtual void moveBackwards();

	virtual void atack() = 0;
	virtual void updateAtack() = 0;

	void update(double p_time, double p_deltaTime);

protected:
	float	m_directionMoveX;
	float	m_directionMoveY;
	float	m_velocity;
	float	m_baseVelocity;
	float	m_damage;

	Player* m_objectivePlayer;
	double	m_distanceToObjective;

	double	m_time;
	double	m_deltaTime;

	bool	m_atackInCooldown;
	float	m_cooldownAtack;
	float	m_endCooldown;

private:
	float	m_health;
	float	m_maxHealth;
	float	m_mana;
	float	m_maxMana;
	float	m_atackSpeed;

	bool	m_dead;
	bool	m_cooperativeMode;

};