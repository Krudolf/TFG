#include "pch.h"
#include "enemyRanger.h"
#include "engineManager.h"
#include "projectile.h"
#include "projectileStraight.h"
#include "fillBar.h"
#include "screenGame.h"


EnemyRanger::EnemyRanger(float p_posX, float p_posY, const char* p_path, int p_waveNumber) : Enemy(p_posX, p_posY, p_path, Entities::ENEMY)
{
	float t_damageFactor = p_waveNumber * 1.4f;
	float t_healthFactor = p_waveNumber * 1.1f;
	float t_expFactor = p_waveNumber * 1.05f;

	m_expToPlayer = 8 + t_expFactor;

	m_damage	= 10 + t_damageFactor;
	m_maxHealth = 75 + t_healthFactor;
	m_health	= m_maxHealth;

	m_cooldownAtack = 5.f;

	m_projectileLaunched = false;
}


EnemyRanger::~EnemyRanger()
{
	if (m_projectileLaunched && m_projectile != nullptr) {
		delete m_projectile;
		m_projectile = nullptr;
	}
}

void EnemyRanger::atack()
{
	if (!m_atackInCooldown && m_projectile == nullptr && m_distanceToObjective <= 600) {
		m_endCooldown = m_engineManager->getMasterClockSeconds() + m_cooldownAtack;
		m_projectile = new ProjectileStraight(m_texturePath, Entities::ENEMY_BULLET, m_posX, m_posY, m_damage, m_directionMoveX, m_directionMoveY);
		ScreenGame::m_projectileVector.push_back(m_projectile);
		m_projectileLaunched = true;
		m_atackInCooldown = true;
	}
}

void EnemyRanger::updateAtack()
{
	if (m_projectileLaunched) {
		m_projectile->update(m_time, m_deltaTime);
		if (m_projectile->getReadyToDelete()) {
			delete m_projectile;
			m_projectile = nullptr;
			m_projectileLaunched = false;
		}
	}
	else if (m_engineManager->getMasterClockSeconds() >= m_endCooldown)
		m_atackInCooldown = false;
}

void EnemyRanger::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));

	if (m_projectileLaunched)
		m_projectile->draw();

	if (m_health != m_maxHealth)
		m_healthBar->draw();
}

