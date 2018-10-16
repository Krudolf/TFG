#pragma once
#include "entity.h"
#include <vector>

class Entity;
class Projectile;

class Player :
	public Entity
{
public:
	Player(float p_posX, float p_posY, const char* p_path);
	~Player();

	void increaseHealth(float p_health);
	void increaseMana(float p_mana);
	void increaseSpeed(float p_duration);
	
	void move();
	void rangeAtack();
	void launchProjectile(Direction p_dir);

	void pickObject();
	
	void updateBasicAtack();
	void updatePotionEffects();
	void update(float p_deltaTime);
	void draw() override;

private:
	double	m_deltaTime;

	float	m_velocity;
	float	m_baseVelocity;
	float	m_health;
	float	m_maxHealth;
	float	m_mana;
	float	m_maxMana;
	float	m_damage;
	float	m_atackSpeed;
	
	bool	m_speedPotionEfect;
	float	m_endOfSpeedPotionEffect;

	bool	m_basicInCooldown;
	float	m_nextBasic;
	
	std::vector<Projectile*> m_basicProjectiles;
	const int m_maxProjectiles = 10;
};