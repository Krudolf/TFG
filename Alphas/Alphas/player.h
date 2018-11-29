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

	void receiveDamage(float p_damage);

	void increaseHealth(float p_health);
	void increaseMana(float p_mana);
	void increaseSpeed(float p_duration, float p_speedIncrease);
	void increaseDamage(float p_duration, float p_damageIncrease);
	void increaseArmor(float p_duration, float p_armorIncrease);
	void increaseAtackSpeed(float p_duration, float p_atackSpeedIncrease);
	
	void move();
	void rangeAtack();
	void hability1();
	void hability2();
	void hability3();
	void updateHabilities();
	void launchProjectile(Direction p_dir, ProjectileType p_ptojectileType);

	void pickObject();
	
	void updateBasicAtack();
	void updatePotionEffects();
	void update(double p_time, double p_deltaTime);
	void draw() override;

private:
	double	m_deltaTime;
	double	m_time;

	bool	m_playerAlive;

	float	m_baseVelocity;
	float	m_velocity;
	float	m_maxHealth;
	float	m_health;
	float	m_maxMana;
	float	m_mana;
	float	m_baseDamage;
	float	m_damage;
	float	m_baseAtackSpeed;
	float	m_atackSpeed;
	float	m_baseArmor;
	float	m_armor;
	
	bool	m_speedPotionEfect;
	bool	m_damagePotionEfect;
	bool	m_armorPotionEfect;
	bool	m_atackSpeedPotionEfect;
	
	float	m_endOfSpeedPotionEffect;
	float	m_endOfDamagePotionEffect;
	float	m_endOfArmorPotionEffect;
	float	m_endOfAtackSpeedPotionEffect;

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