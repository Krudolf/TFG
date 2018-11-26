#pragma once
#include "entity.h"
#include <vector>

class Entity;
class Projectile;
class ProjectileSpin;
class ProjectileStraightSpin;
class ProjectileConus;

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
	void hability1();
	void hability2();
	void hability3();
	void hability4();
	void launchProjectile(Direction p_dir, ProjectileType p_ptojectileType);

	void pickObject();
	
	void updateBasicAtack();
	void updatePotionEffects();
	void update(double p_time, double p_deltaTime);
	void draw() override;

private:
	double	m_deltaTime;
	double	m_time;

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

	Direction m_faceDirection;

	ProjectileSpin*			m_hability1;
	ProjectileStraightSpin* m_hability2;
	ProjectileConus*		m_hability3;
	Projectile*				m_hability4;
	
	bool m_hability1Launched;
	bool m_hability2Launched;
	bool m_hability3Launched;
	bool m_hability4Launched;
	
	std::vector<Projectile*> m_basicProjectiles;
	const int m_maxProjectiles = 10;
};