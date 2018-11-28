#include "pch.h"
#include "enemyRanger.h"
#include "engineManager.h"
#include "projectile.h"
#include "projectileStraight.h"

EnemyRanger::EnemyRanger(float p_posX, float p_posY, const char* p_path) : Enemy(p_posX, p_posY, p_path)
{
	m_damage = 10;

	m_cooldownAtack = 5.f;

	m_projectileLaunched = false;
}


EnemyRanger::~EnemyRanger()
{
}

void EnemyRanger::atack()
{
	if (!m_atackInCooldown && m_projectile == nullptr && m_distanceToObjective <= 600) {
		m_endCooldown = m_engineManager->getMasterClockSeconds() + m_cooldownAtack;
		m_projectile = new ProjectileStraight(m_texturePath, Entities::BULLET2, m_posX, m_posY, m_damage, m_directionMoveX, m_directionMoveY);
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
}

