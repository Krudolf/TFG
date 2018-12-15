#include "pch.h"
#include "playerGreen.h"
#include "engineManager.h"
#include "projectileSpinFixed.h"
#include "projectileStraightSticky.h"
#include "projectileStraightStun.h"


PlayerGreen::PlayerGreen(float p_posX, float p_posY, const char * p_path) : Player(p_posX, p_posY, p_path, Entities::PLAYER2)
{
	m_bulletColor = Entities::BULLET2;

	m_baseDamage = 10.f;
	m_damage = m_baseDamage;
	m_maxHealth = 125.f;
	m_health = m_maxHealth;
	m_maxMana = 200.f;
	m_mana = m_maxMana;
	m_baseArmor = 5.f;
	m_armor = m_baseArmor;
	m_baseVelocity = 95.f;
	m_velocity = m_baseVelocity;
	m_baseAtackSpeed = 0.3f;
	m_atackSpeed = m_baseAtackSpeed;

	m_hability1ManaConsumption = 20.f;
	m_hability2ManaConsumption = 60.f;
	m_hability3ManaConsumption = 50.f;
}


PlayerGreen::~PlayerGreen()
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

void PlayerGreen::hability1()
{
	if (enoughMana(m_hability1ManaConsumption)) {
		m_hability1CooldownDuration = 5.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability1 = new ProjectileStraightStun(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage/5, true, true);
		m_hability1Launched = true;
	}
}

void PlayerGreen::hability2()
{
	if (enoughMana(m_hability2ManaConsumption)) {
		m_hability2CooldownDuration = 5.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability2 = new ProjectileSpinFixed(m_texturePath, m_bulletColor, Direction::NONE, m_posX, m_posY, m_damage/2);
		m_hability2Launched = true;
	}
}

void PlayerGreen::hability3()
{
	if (enoughMana(m_hability3ManaConsumption)) {
		m_hability3CooldownDuration = 10.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability3 = new ProjectileStraightSticky(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage);
		m_hability3Launched = true;
	}
}
