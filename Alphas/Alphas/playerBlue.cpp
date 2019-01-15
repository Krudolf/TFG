#include "pch.h"
#include "playerBlue.h"
#include "engineManager.h"
#include "projectileSpin.h"
#include "projectileStraightSpin.h"
#include "projectileConus.h"
#include "screenGame.h"


PlayerBlue::PlayerBlue(float p_posX, float p_posY, const char * p_path) : Player(p_posX, p_posY, p_path, Entities::PLAYER_BLUE)
{
	m_bulletColor = Entities::BULLET_BLUE;

	m_baseDamage	 = 10.f;
	m_damage		 = m_baseDamage;
	m_maxHealth		 = 100.f;
	m_health		 = m_maxHealth;
	m_maxMana		 = 225.f;
	m_mana			 = m_maxMana;
	m_baseArmor		 = 3.f;
	m_armor			 = m_baseArmor;
	m_baseVelocity	 = 100.f;
	m_velocity		 = m_baseVelocity;
	m_baseAtackSpeed = 0.25f;
	m_atackSpeed	 = m_baseAtackSpeed;

	m_hability1ManaConsumption = 20.f;
	m_hability2ManaConsumption = 45.f;
	m_hability3ManaConsumption = 65.f;
}

PlayerBlue::~PlayerBlue()
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

void PlayerBlue::levelStats()
{
	m_baseDamage = 10.f + (m_level * 1.2f);
	m_damage = m_baseDamage;
	m_maxHealth = 100.f + (m_level * 10.f);
	m_health = m_maxHealth;
	m_maxMana = 225.f + (m_level * 12.f);
	m_mana = m_maxMana;
	m_baseArmor = 3.f + (m_level * 0.7f);
	m_armor = m_baseArmor;
	m_baseAtackSpeed = 0.25f - (m_level * 0.002f);
	m_atackSpeed = m_baseAtackSpeed;
}

void PlayerBlue::hability1()
{
	if (enoughMana(m_hability1ManaConsumption)) {
		m_hability1CooldownDuration = 5.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability1 = new ProjectileConus(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage*2, true, true);
		m_hability1->setOwner(this);
		ScreenGame::m_projectileVector.push_back(m_hability1);
		m_hability1Launched = true;
	}
}

void PlayerBlue::hability2()
{
	if (enoughMana(m_hability2ManaConsumption)) {
		m_hability2CooldownDuration = 5.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability2 = new ProjectileSpin(m_texturePath, m_bulletColor, Direction::NONE, m_damage*1.2, this, true, true);
		m_hability2->setOwner(this);
		ScreenGame::m_projectileVector.push_back(m_hability2);
		m_hability2Launched = true;
	}
}

void PlayerBlue::hability3()
{
	if (enoughMana(m_hability3ManaConsumption)) {
		m_hability3CooldownDuration = 10.f;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		m_hability3 = new ProjectileStraightSpin(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage*1.5, this);
		m_hability3->setOwner(this);
		ScreenGame::m_projectileVector.push_back(m_hability3);
		m_hability3Launched = true;
	}
}