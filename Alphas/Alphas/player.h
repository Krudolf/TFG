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
	Player(float p_posX, float p_posY, const char* p_path, Entities p_playerEntity);
	virtual ~Player();

	float getHealth() { return m_health; };
	float getMaxHealth() { return m_maxHealth; };
	float getMana() { return m_mana; };
	float getMaxMana() { return m_maxMana; };
	float getVelocity() { return m_velocity; };
	float getDamage() { return m_damage; };
	float getArmor() { return m_armor; };
	float getAtackSpeed() { return m_atackSpeed; };

	void receiveDamage(float p_damage);

	void increaseHealth(float p_health);
	void increaseMana(float p_mana);
	void increaseSpeed(float p_duration, float p_speedIncrease);
	void increaseDamage(float p_duration, float p_damageIncrease);
	void increaseArmor(float p_duration, float p_armorIncrease);
	void increaseAtackSpeed(float p_duration, float p_atackSpeedIncrease);
	
	void move();
	void rangeAtack();
	virtual void hability1() = 0;
	virtual void hability2() = 0;
	virtual void hability3() = 0;
	void updateHabilities();
	void launchProjectile(Direction p_dir, ProjectileType p_ptojectileType);

	void pickObject();
	
	void updateBasicAtack();
	void updatePotionEffects();
	void update(double p_time, double p_deltaTime);
	void draw() override;

protected:
	float	m_maxHealth;
	float	m_health;
	float	m_maxMana;
	float	m_mana;
	float	m_baseVelocity;
	float	m_velocity;
	float	m_baseDamage;
	float	m_damage;
	float	m_baseArmor;
	float	m_armor;
	float	m_baseAtackSpeed;
	float	m_atackSpeed;

	Entities	m_bulletColor;

	Direction	m_faceDirection;

	Projectile*	m_hability1;
	Projectile*	m_hability2;
	Projectile*	m_hability3;
	
	bool m_hability1Launched;
	bool m_hability2Launched;
	bool m_hability3Launched;
	bool m_hability4Launched;

private:
	double	m_deltaTime;
	double	m_time;

	bool	m_playerAlive;
	
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

	std::vector<Projectile*> m_basicProjectiles;
	const int m_maxProjectiles = 10;
};