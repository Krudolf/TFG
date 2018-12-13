#include "pch.h"
#include "enemyWarrior.h"
#include "engineManager.h"
#include "player.h"

#include <iostream>

EnemyWarrior::EnemyWarrior(float p_posX, float p_posY, const char* p_path) : Enemy(p_posX, p_posY, p_path, Entities::ENEMY)
{
	m_damage = 5;
	m_velocity *= 1.5;
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