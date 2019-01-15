#include "pch.h"
#include "enemyCharger.h"
#include "engineManager.h"
#include "player.h"
#include "fillBar.h"
#include "hashGrid.h"
#include "tile.h"

#include <iostream>


EnemyCharger::EnemyCharger(float p_posX, float p_posY, const char* p_path, int p_waveNumber) : Enemy(p_posX, p_posY, p_path, Entities::ENEMY)
{
	float t_damageFactor = p_waveNumber * 1.25f;
	float t_healthFactor = p_waveNumber * 1.25f;
	float t_expFactor = p_waveNumber * 1.15f;

	m_expToPlayer = 12 + t_expFactor;

	m_damage	= 20 + t_damageFactor;
	m_maxHealth = 100 + t_healthFactor;
	m_health	= m_maxHealth;

	m_chargePhase	= false;
	m_releasePhase	= false;
	m_lockDirection = false;

	m_chargeTime	= 1.5f;
	m_releaseTime	= 1.25f;
	m_cooldownAtack = m_chargeTime + m_releaseTime + 3.f;
	m_endChargeTime = -1;
	m_endReleaseTime = -1;
}


EnemyCharger::~EnemyCharger()
{
}

void EnemyCharger::moveBackwards()
{
	if (!m_releasePhase) {
		m_posX = m_lastPosX + (m_deltaTime * m_velocity * -m_directionMoveX);
		m_posY = m_lastPosY + (m_deltaTime * m_velocity * -m_directionMoveY);
	}
}

void EnemyCharger::atack()
{
	if (!m_atackInCooldown) {
		float t_time = m_engineManager->getMasterClockSeconds();

		//If not charging atack and not doing the atack and the enemy is in range --> starts to charge the atack
		if (!m_chargePhase && !m_releasePhase && m_distanceToObjective <= 500) {
			m_chargePhase = true;
			m_endChargeTime = t_time + m_chargeTime;
			m_endCooldown = t_time + m_cooldownAtack;
		}
	}
}

void EnemyCharger::updateAtack()
{
	if (!m_stunned) {
		float t_time = m_engineManager->getMasterClockSeconds();

		//charge time ends --> charge phase ends --> starts release phase
		if (m_chargePhase && t_time >= m_endChargeTime) {
			m_chargePhase	= false;
			m_releasePhase	= true;
			m_endReleaseTime = m_endChargeTime = t_time + m_releaseTime;
		}

		//Release phase
		if (m_releasePhase) {
			//Lock the direction that the enemy will follow during charge and increase the speed
			if (!m_lockDirection) {
				m_lockDirection = true;
				m_velocity *= 6;
				m_engineManager->getDirection(m_objectivePlayer->getPositionX(), m_objectivePlayer->getPositionY(), m_posX, m_posY, m_directionMoveX, m_directionMoveY);
			}

			move();

			bool t_collision = false;
			for (auto t_object : m_nearEntityVector) {
				if (t_object->getEntity() == Entities::TILE) {
					if (m_engineManager->checkCollision(m_spriteID, t_object->getSpriteID())) {
						Tile* t_tile = dynamic_cast<Tile*>(t_object);
						t_tile->applyEffect(this);

						if (m_releasePhase && t_tile->getTileType() == TileTypes::BLOCK) {
							m_velocity = m_baseVelocity;
							m_lockDirection = false;
							m_releasePhase = false;
							m_atackInCooldown = true;
						}
					}
				}
				else if (t_object->getEntity() == Entities::PLAYER_BLUE || t_object->getEntity() == Entities::PLAYER_GREEN || t_object->getEntity() == Entities::PLAYER_YELLOW) {
					if (m_engineManager->checkCollision(t_object->getSpriteID(), m_spriteID)) {
						Player* t_player = dynamic_cast<Player*>(t_object);
						t_player->receiveDamage(m_damage);

						t_collision = true;
					}
				}
			}
			if (t_collision || t_time >= m_endReleaseTime) {
				m_velocity			= m_baseVelocity;
				m_lockDirection		= false;
				m_releasePhase		= false;
				m_atackInCooldown	= true;
			}
		}
	}
	else {
		m_velocity			= m_baseVelocity;
		m_lockDirection		= false;
		m_chargePhase		= false;
		m_releasePhase		= false;
		m_atackInCooldown	= true;
	}
}

void EnemyCharger::update(double p_time, double p_deltaTime)
{
	m_deltaTime = p_deltaTime;

	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	if (!m_chargePhase && !m_releasePhase) {
		checkObjective();
		move();
	}
	
	atack();
	updateAtack();

	m_nearEntityVector = m_hashGrid->getNearby(this);
	for (auto t_object : m_nearEntityVector) {
		if (t_object->getEntity() == Entities::TILE) {
			if (m_engineManager->checkCollision(m_spriteID, t_object->getSpriteID())) {
				Tile* t_tile = dynamic_cast<Tile*>(t_object);
				t_tile->applyEffect(this);
			}
		}
	}

	if (m_atackInCooldown && m_engineManager->getMasterClockSeconds() >= m_endCooldown)
		m_atackInCooldown = false;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
	m_healthBar->update(m_health / m_maxHealth, m_posX, m_posY);
}
