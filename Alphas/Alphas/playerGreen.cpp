#include "pch.h"
#include "playerGreen.h"
#include "engineManager.h"
#include "projectileSpin.h"
#include "projectileStraightSpin.h"
#include "projectileConus.h"


PlayerGreen::PlayerGreen(float p_posX, float p_posY, const char * p_path) : Player(p_posX, p_posY, p_path, Entities::PLAYER2)
{
	m_bulletColor = Entities::BULLET2;

	m_baseVelocity = 100.f;
	m_velocity = m_baseVelocity;
	m_maxHealth = 100.f;
	m_health = m_maxHealth;
	m_maxMana = 100.f;
	m_mana = m_maxMana;
	m_baseDamage = 1.f;
	m_damage = m_baseDamage;
	m_baseAtackSpeed = 0.25f;
	m_atackSpeed = m_baseAtackSpeed;
	m_baseArmor = 1.f;
	m_armor = m_baseArmor;
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
	m_hability1Launched = true;
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	m_hability1 = new ProjectileStraightSpin(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage);
}

void PlayerGreen::hability2()
{
	m_hability2Launched = true;
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	m_hability2 = new ProjectileConus(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage);
}

void PlayerGreen::hability3()
{
	m_hability3Launched = true;
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	m_hability3 = new ProjectileSpin(m_texturePath, m_bulletColor, Direction::NONE, m_posX, m_posY, m_damage / 10, this);
}
