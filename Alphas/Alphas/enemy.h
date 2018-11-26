#pragma once
#include "entity.h"

class Player;

class Enemy : 
	public Entity
{
public:
	Enemy(float p_posX, float p_posY, const char* p_path);
	~Enemy();

	void receiveDamage(float p_damage);
	bool isDead() { return m_dead; };

	void checkObjective();
	float calculateDistance(Player* p_posibleObjective);
	void move();
	float getDistanceToObjective() { return m_distanceToObjective; };
	void moveBackwards();
	void goLastPosition();

	void update(double p_time, double p_deltaTime);

private:
	float	m_directionMoveX;
	float	m_directionMoveY;
	float	m_velocity;
	float	m_baseVelocity;
	float	m_health;
	float	m_maxHealth;
	float	m_mana;
	float	m_maxMana;
	float	m_damage;
	float	m_atackSpeed;

	double m_deltaTime;
	
	bool	m_dead;
	bool	m_cooperativeMode;

	Player* m_objectivePlayer;
	float	m_distanceToObjective;

};