#include "pch.h"
#include "enemyWarrior.h"
#include "engineManager.h"
#include "player.h"

EnemyWarrior::EnemyWarrior(float p_posX, float p_posY, const char* p_path, int p_waveNumber) : Enemy(p_posX, p_posY, p_path, Entities::ENEMY)
{
	float t_damageFactor = p_waveNumber * 1.1f;
	float t_healthFactor = p_waveNumber * 1.2f;
	float t_expFactor	 = p_waveNumber * 1.1f;

	m_expToPlayer = 10 + t_expFactor;

	m_velocity	*= 1.5;
	m_damage	 = 5 + t_damageFactor;
	m_maxHealth  = 150 + t_healthFactor;
	m_health	 = m_maxHealth;
}


EnemyWarrior::~EnemyWarrior()
{
}

void EnemyWarrior::atack()
{
	if (m_distanceToObjective < 35) {
		if (!m_atackInCooldown && m_engineManager->checkCollision(m_spriteID, m_objectivePlayer->getSpriteID())) {
			m_objectivePlayer->receiveDamage(m_damage);
			m_endCooldown = m_engineManager->getMasterClockSeconds() + m_cooldownAtack;
			m_atackInCooldown = true;
		}
	}
}

void EnemyWarrior::updateAtack()
{
	if (m_engineManager->getMasterClockSeconds() >= m_endCooldown)
		m_atackInCooldown = false;
}