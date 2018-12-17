#include "pch.h"
#include "playerYellow.h"
#include "engineManager.h"
#include "projectileConus.h"
#include "projectileSpin.h"

#include "projectileStraight.h"


PlayerYellow::PlayerYellow(float p_posX, float p_posY, const char * p_path) : Player(p_posX, p_posY, p_path, Entities::PLAYER_YELLOW)
{
	m_bulletColor = Entities::BULLET_YELLOW;

	m_baseDamage = 15.f;
	m_damage = m_baseDamage;
	m_maxHealth = 100.f;
	m_health = m_maxHealth;
	m_maxMana = 200.f;
	m_mana = m_maxMana;
	m_baseArmor = 1.f;
	m_armor = m_baseArmor;
	m_baseVelocity = 120.f;
	m_velocity = m_baseVelocity;
	m_baseAtackSpeed = 0.15f;
	m_atackSpeed = m_baseAtackSpeed;

	m_hability1ManaConsumption = 30.f;
	m_hability2ManaConsumption = 55.f;
	m_hability3ManaConsumption = 40.f;
}


PlayerYellow::~PlayerYellow()
{
	if (m_hability1 != nullptr) {
		delete m_hability1;
		m_hability1 = nullptr;
	}

	if (m_hability2 != nullptr) {
		delete m_hability2;
		m_hability2 = nullptr;
	}

	if (m_hability3 != nullptr) {
		delete m_hability3;
		m_hability3 = nullptr;
	}
}

void PlayerYellow::hability1()
{
	if (enoughMana(m_hability1ManaConsumption)) {
		m_hability1CooldownDuration = 5.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability1 = new ProjectileConus(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage*1.5, true, false);
		m_hability1Launched = true;
	}
}

void PlayerYellow::hability2()
{
	if (enoughMana(m_hability2ManaConsumption)) {
		m_hability2CooldownDuration = 5.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability2 = new ProjectileSpin(m_texturePath, m_bulletColor, Direction::NONE, m_damage*0, this, true, false);
		m_hability2Launched = true;
	}
}

void PlayerYellow::hability3()
{
	if (enoughMana(m_hability3ManaConsumption)) {
		m_hability3CooldownDuration = 10.f;
		m_damage *= 1.25f;
		m_pasiveActive = true;
		m_hability3inCooldown = true;
		m_hability3ActivationTime = m_engineManager->getMasterClockSeconds();
	}
}

void PlayerYellow::updateHability3()
{
	float t_time = m_engineManager->getMasterClockSeconds();

	if (m_hability3inCooldown) {
		if (t_time >= (m_hability3ActivationTime + m_hability3CooldownDuration)) {
			m_hability3inCooldown = false;
		}
		else if (t_time >= (m_hability3ActivationTime + m_hability3CooldownDuration - 5.f)) {
			m_pasiveActive = false;
			m_damage = m_baseDamage;
		}
	}
}
