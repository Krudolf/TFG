#pragma once
#include "entity.h"

class Player;
class Projectile;
class FillBar;

class Enemy : 
	public Entity
{
public:
	Enemy(float p_posX, float p_posY, const char* p_path, Entities p_entity);
	virtual ~Enemy();

	void receiveDamage(float p_damage, Projectile* p_projectile);
	void receiveTrapDamage(float p_damage);
	bool isDead() { return (m_dead && !m_sticky); };

	void checkObjective();
	void move();
	virtual void moveBackwards();
	double getDistanceToObjective() { return m_distanceToObjective; };

	virtual void atack() = 0;
	virtual void updateAtack() = 0;

	void update(double p_time, double p_deltaTime);
	void draw() override;

	void setStunned(float p_timeStunned);
	void setSticky(float p_sticky) { m_sticky = p_sticky; };

protected:
	bool	m_stunned;
	bool	m_sticky;

	float	m_maxHealth;
	float	m_health;
	float	m_damage;
	float	m_atackSpeed;
	float	m_velocity;
	float	m_baseVelocity;

	Player* m_objectivePlayer;
	double	m_distanceToObjective;
	float	m_directionMoveX;
	float	m_directionMoveY;

	double	m_time;
	double	m_deltaTime;

	bool	m_atackInCooldown;
	float	m_cooldownAtack;
	float	m_endCooldown;

	FillBar*	m_healthBar;

private:
	double calculateDistance(Player* p_posibleObjective);

	Projectile*	m_lastProjectile;
	float		m_timeNextHitProjectile;
	float		m_timeNextHitTrap;

	bool	m_dead;
	bool	m_cooperativeMode;

	float	m_endOfStun;

};