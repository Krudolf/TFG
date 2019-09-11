#pragma once
#include "entity.h"
#include <vector>

class Entity;
class Projectile;

class Player :
	public Entity
{
public:
	Player(float p_posX, float p_posY, const char* p_path, Entities p_playerEntity);
	virtual ~Player();

	bool	getAlive()		{ return m_alive; };
	float	getHealth()		{ return m_health; };
	float	getMaxHealth()	{ return m_maxHealth; };
	float	getMana()		{ return m_mana; };
	float	getMaxMana()	{ return m_maxMana; };
	float	getVelocity()	{ return m_velocity; };
	float	getDamage()		{ return m_damage; };
	float	getArmor()		{ return m_armor; };
	float	getAtackSpeed() { return m_atackSpeed; };
	int		getLevel()		{ return m_level; };
	float	getCurrentExp() { return m_currentExperience; };
	float	getTopExp()		{ return m_topExperience; };

	void	receiveDamage(float p_damage);
	void	receiveDamage(float p_damage, Projectile* p_projectile);
	void	receiveTrapDamage(float p_damage);
	void	receiveExperience(float p_experience);
	virtual void	levelStats() = 0;

	void	increaseHealth(float p_health);
	void	increaseMana(float p_mana);
	void	increaseSpeed(float p_duration, float p_speedIncrease);
	void	increaseDamage(float p_duration, float p_damageIncrease);
	void	increaseArmor(float p_duration, float p_armorIncrease);
	void	increaseAtackSpeed(float p_duration, float p_atackSpeedIncrease);
	
	void	move();
	void	moveBackwards();
	void	rangeAtack();
	bool	enoughMana(float p_mana);
	virtual void hability1() = 0;
	virtual void hability2() = 0;
	virtual void hability3() = 0;

	bool	getHability1EnoughMana() { return m_hability1EnoughMana; };
	bool	getHability2EnoughMana() { return m_hability2EnoughMana; };
	bool	getHability3EnoughMana() { return m_hability3EnoughMana; };

	float	getHability1CooldownDuration() { return m_hability1CooldownDuration; };
	float	getHability2CooldownDuration() { return m_hability2CooldownDuration; };
	float	getHability3CooldownDuration() { return m_hability3CooldownDuration; };

	float	getHability1ActivationTime() { return m_hability1ActivationTime; };
	float	getHability2ActivationTime() { return m_hability2ActivationTime; };
	float	getHability3ActivationTime() { return m_hability3ActivationTime; };
	virtual void updateHability1();
	virtual void updateHability2();
	virtual void updateHability3();
	void updateManaConsumption();
	void launchProjectile();

	void pickPotion();
	
	void updateHealthAndMana(double p_deltaTime);
	void updateBasicAtack();
	void updatePotionEffects();
	void update(double p_time, double p_deltaTime);
	void draw() override;

	void setKeyboardControll(bool p_keyboard) { m_keyboard = p_keyboard; };
	bool getKeyboardControll() { return m_keyboard; };

protected:
	double	m_deltaTime;
	double	m_time;

	bool	m_alive;

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

	int		m_level;
	float	m_baseExperience;
	float	m_experienceFactor;
	float	m_currentExperience;
	float	m_topExperience;

	bool	m_pasiveActive;

	Entities	m_bulletColor;

	Direction	m_faceDirection;

	Projectile*	m_hability1;
	Projectile*	m_hability2;
	Projectile*	m_hability3;
	
	bool m_hability1Launched;
	bool m_hability2Launched;
	bool m_hability3Launched;
	bool m_hability1inCooldown;
	bool m_hability2inCooldown;
	bool m_hability3inCooldown;
	bool m_hability1EnoughMana;
	bool m_hability2EnoughMana;
	bool m_hability3EnoughMana;

	float	m_hability1ManaConsumption;
	float	m_hability2ManaConsumption;
	float	m_hability3ManaConsumption;
	float	m_hability1CooldownDuration;
	float	m_hability2CooldownDuration;
	float	m_hability3CooldownDuration;
	float	m_hability1ActivationTime;
	float	m_hability2ActivationTime;
	float	m_hability3ActivationTime;

private:
	const int m_maxProjectiles = 20;

	bool	m_keyboard;
	
	bool	m_nearPotion;
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

	Projectile*	m_lastProjectile;
	float		m_timeNextHitProjectile;
	float		m_timeNextHitTrap;

	std::vector<Projectile*>	m_basicProjectiles;
};