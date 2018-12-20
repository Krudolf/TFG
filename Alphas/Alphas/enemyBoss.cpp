#include "pch.h"
#include "enemyBoss.h"
#include "enemyWarrior.h"
#include "enemyCharger.h"
#include "enemyRanger.h"
#include "engineManager.h"
#include "projectile.h"
#include "projectileStraight.h"
#include "player.h"
#include "Point.h"
#include "screenGame.h"
#include "fillBar.h"
#include "tile.h"

#include <iostream>

EnemyBoss::EnemyBoss(float p_posX, float p_posY, const char* p_path) : Enemy(p_posX, p_posY, p_path, Entities::ENEMY_BOSS)
{
	m_damage = 30;
	m_baseVelocity *= 1.2f;
	m_velocity *= 1.2f;
	m_maxHealth = 500.f;
	m_health = m_maxHealth;

	m_secondProjectileTime = 0.f;
	m_chargeTime = 1.5f;
	m_releaseTime = 1.25f;
	m_endChargeTime = -1;
	m_endReleaseTime = -1;

	m_rangeAttackCooldown = 6.f;
	m_chargeAttackCooldown = m_chargeTime + m_releaseTime + 5.f;;
	m_spawnMinionCooldown = 10.f;
	m_rangeAttackEndCooldown = 0.f;
	m_chargeAttackEndCooldown = 0.f;
	m_spawnMinionEndCooldown = m_engineManager->getMasterClockSeconds() + m_spawnMinionCooldown;
	
	m_attackSelected = false;
	m_rangeAttackSelected = false;
	m_chargeAttackSelected = false;

	m_rangeAttackLaunched = false;
	m_chargeAttackLaunched = false;

	m_firstProjectileLaunched = false;
	m_chargePhase = false;
	m_releasePhase = false;
	m_lockDirection = false;

	m_rangeAttackInCooldown = false;
	m_chargeAttackInCooldown = false;
}


EnemyBoss::~EnemyBoss()
{
	if (m_rangeAttackLaunched) {
		for (auto t_projectile : m_projectilesVector) {
			delete t_projectile;
			t_projectile = nullptr;
		}
	}
	m_projectilesVector.clear();
}

void EnemyBoss::selectAttack()
{
	if (!m_rangeAttackInCooldown && m_distanceToObjective > 700 && m_distanceToObjective <= 1200 && !m_firstProjectileLaunched) {
		m_rangeAttackSelected = true;
		m_attackSelected = true;
	}
	else if (!m_chargeAttackInCooldown && !m_chargePhase && !m_releasePhase && m_distanceToObjective <= 700) {
		m_chargeAttackSelected = true;
		m_attackSelected = true;
	}
	else if (m_engineManager->getMasterClockSeconds() >= m_spawnMinionEndCooldown) {
		spawnMinion();
	}
}

void EnemyBoss::atack()
{
	if (!m_attackSelected)
		selectAttack();
	else{
		if(m_rangeAttackSelected)
			rangeAtack();
		else if (m_chargeAttackSelected)
			chargeAttack();
	}
}

void EnemyBoss::chargeAttack()
{
	//If not charging atack and not doing the atack and the enemy is in range --> starts to charge the atack
	if (!m_chargePhase && !m_releasePhase && m_distanceToObjective <= 500) {
		m_chargePhase = true;
		float t_time = m_engineManager->getMasterClockSeconds();
		m_endChargeTime = t_time + m_chargeTime;
		m_endCooldown = t_time + m_chargeAttackCooldown;

		m_chargeAttackSelected = false;
		m_attackSelected = false;
	}
}

void EnemyBoss::rangeAtack()
{
	if (!m_firstProjectileLaunched) {
		m_firstProjectileLaunched = true;
		m_secondProjectileTime = m_engineManager->getMasterClockSeconds() + 0.4;
		launchProjectile();
	}
	else if(m_engineManager->getMasterClockSeconds() >= m_secondProjectileTime) {
		m_rangeAttackEndCooldown = m_engineManager->getMasterClockSeconds() + m_rangeAttackCooldown;
		m_rangeAttackLaunched = true;
		m_rangeAttackInCooldown = true;
		launchProjectile();

		m_rangeAttackSelected = false;
		m_attackSelected = false;
	}
}

void EnemyBoss::spawnMinion()
{
	createEnemy(EnemyType::RANGER);
	createEnemy(EnemyType::CHARGER);
	createEnemy(EnemyType::RANGER);

	m_spawnMinionEndCooldown = m_engineManager->getMasterClockSeconds() + m_spawnMinionCooldown;
}

void EnemyBoss::launchProjectile()
{
	Projectile* t_projectile = new ProjectileStraight(m_texturePath, Entities::ENEMY_BOSS_BULLET, m_posX, m_posY, m_damage/2, m_directionMoveX*2, m_directionMoveY*2);
	m_projectilesVector.push_back(t_projectile);
	ScreenGame::m_projectileVector.push_back(t_projectile);
}

void EnemyBoss::createEnemy(EnemyType p_type)
{
	Point t_point = { m_posX, m_posY };
	t_point.x += ((rand() % 101) - 50);
	t_point.y += ((rand() % 101) - 50);

	Enemy* t_enemy;
	switch (p_type)
	{
	case EnemyType::WARRIOR:
		t_enemy = new EnemyWarrior(t_point.x, t_point.y, "assets/spritesheet.png");
		break;
	case EnemyType::CHARGER:
		t_enemy = new EnemyCharger(t_point.x, t_point.y, "assets/spritesheet.png");
		break;
	case EnemyType::RANGER:
		t_enemy = new EnemyRanger(t_point.x, t_point.y, "assets/spritesheet.png");
		break;
	default:
		break;
	}
	ScreenGame::m_enemyVector.push_back(t_enemy);
}

void EnemyBoss::updateAtack()
{
	updateRangeAttack();

	updateChargeAttack();
}

void EnemyBoss::updateRangeAttack()
{
	if (m_rangeAttackLaunched) {
		for (int i = 0; i < m_projectilesVector.size(); i++) {
			m_projectilesVector[i]->update(m_time, m_deltaTime);
			if (m_projectilesVector[i]->getReadyToDelete()) {
				delete m_projectilesVector[i];
				m_projectilesVector[i] = nullptr;
				m_projectilesVector.erase(m_projectilesVector.begin() + i);
				
			}
		}
		if (m_projectilesVector.size() == 0) {
			m_rangeAttackLaunched = false;
			m_firstProjectileLaunched = false;
		}
	}
	else if (m_engineManager->getMasterClockSeconds() >= m_rangeAttackEndCooldown)
		m_rangeAttackInCooldown = false;
}

void EnemyBoss::updateChargeAttack()
{
	float t_time = m_engineManager->getMasterClockSeconds();

	//charge time ends --> charge phase ends --> starts release phase
	if (m_chargePhase && t_time >= m_endChargeTime) {
		m_chargePhase = false;
		m_releasePhase = true;
		m_endReleaseTime = m_endChargeTime = t_time + m_releaseTime;
	}
	else if (m_releasePhase) {
	//Release phase
		//Lock the direction that the enemy will follow during charge and increase the speed
		if (!m_lockDirection) {
			m_lockDirection = true;
			m_velocity *= 5;
			m_engineManager->getDirection(m_objectivePlayer->getPositionX(), m_objectivePlayer->getPositionY(), m_posX, m_posY, m_directionMoveX, m_directionMoveY);
		}

		move();

		bool t_collision = false;
		for (auto t_object : m_nearEntityVector) {
			if (t_object->getEntity() == Entities::TILE) {
				if (m_engineManager->checkCollision(m_spriteID, t_object->getSpriteID())) {
					Tile* t_tile = dynamic_cast<Tile*>(t_object);
					t_tile->applyEffect(this);

					if (m_releasePhase) {
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
			m_velocity = m_baseVelocity;
			m_lockDirection = false;
			m_releasePhase = false;
			m_chargeAttackInCooldown = true;
		}
		
	}
	if (m_chargeAttackInCooldown && m_engineManager->getMasterClockSeconds() >= m_endCooldown) {
		m_chargeAttackInCooldown = false;
	}
}

void EnemyBoss::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));

	if (m_rangeAttackLaunched) {
		for (auto t_projectile : m_projectilesVector) {
			t_projectile->draw();
		}
	}

	if (m_health != m_maxHealth)
		m_healthBar->draw();
}
