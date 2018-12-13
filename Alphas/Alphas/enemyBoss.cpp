#include "pch.h"
#include "enemyBoss.h"
#include "engineManager.h"
#include "projectile.h"
#include "projectileStraight.h"

#include <iostream>

EnemyBoss::EnemyBoss(float p_posX, float p_posY, const char* p_path) : Enemy(p_posX, p_posY, p_path, Entities::ENEMY_BOSS)
{
	m_damage = 30;
	m_velocity *= 1.2;
	m_maxHealth = 500.f;
	m_health = m_maxHealth;

	m_cooldownAtack = 5.f;
	m_projectileLaunched = false;
}


EnemyBoss::~EnemyBoss()
{
	if (m_projectileLaunched && m_projectile != nullptr) {
		delete m_projectile;
		m_projectile = nullptr;
	}
}

void EnemyBoss::atack()
{
	if (!m_atackInCooldown && m_projectile == nullptr && m_distanceToObjective <= 800) {
		m_endCooldown = m_engineManager->getMasterClockSeconds() + m_cooldownAtack;
		m_projectile = new ProjectileStraight(m_texturePath, Entities::ENEMY_BOSS_BULLET, m_posX, m_posY, m_damage, m_directionMoveX, m_directionMoveY);
		m_projectileLaunched = true;
		m_atackInCooldown = true;
	}
}

void EnemyBoss::updateAtack()
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

void EnemyBoss::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));

	if (m_projectileLaunched) {
		std::cout << "PINTAMOOOOOS!!" << std::endl;
		m_projectile->draw();
	}
}
