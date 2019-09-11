#include "pch.h"
#include "enemy.h"
#include "engineManager.h"
#include "screenGame.h"
#include "player.h"
#include "projectile.h"
#include "fillBar.h"
#include "hashGrid.h"
#include "tile.h"

#include <cmath>


Enemy::Enemy(float p_posX, float p_posY, const char* p_path, Entities p_entity) : Entity(p_path, p_entity)
{
	m_posX		= p_posX;
	m_posY		= p_posY;
	m_lastPosX	= p_posX;
	m_lastPosY	= p_posY;

	m_directionMoveX = 0.f;
	m_directionMoveY = 0.f;
	
	m_baseVelocity	= 95.f;
	m_velocity		= m_baseVelocity;
	m_maxHealth		= 100.f;
	m_health		= m_maxHealth;
	m_damage		= 2.f;
	m_atackSpeed	= 0.75f;
	m_dead			= false;
	m_stunned		= false;

	m_cooperativeMode		= ScreenGame::getCooperativeMode();
	m_distanceToObjective	= 1000;
	m_objectivePlayer		= ScreenGame::m_playerVector[0];

	m_atackInCooldown	= true;
	m_cooldownAtack		= 1.f;
	m_endCooldown		= m_engineManager->getMasterClockSeconds() + 2.f;

	m_sticky = false;

	m_lastProjectile = nullptr;
	m_timeNextHitProjectile = 0.f;
	m_timeNextHitTrap = 0.f;

	m_healthBar = new FillBar(50, 10, this->getPositionX(), this->getPositionY(), { 0, 0, 0, 255 }, { 255, 0, 0, 255 });
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}


Enemy::~Enemy()
{
	delete m_healthBar;
	m_healthBar = nullptr;
}

void Enemy::receiveDamage(float p_damage, Projectile* p_projectile)
{
	if (m_lastProjectile != p_projectile) {
		m_health -= p_damage;
		m_lastProjectile = p_projectile;
		m_timeNextHitProjectile = m_engineManager->getMasterClockSeconds() + 0.15;
	}
	else {
		if (m_engineManager->getMasterClockSeconds() >= m_timeNextHitProjectile) {
			m_health -= p_damage;
			m_timeNextHitProjectile = m_engineManager->getMasterClockSeconds() + 0.15;
		}
	}

	if (m_health <= 0.f && !m_dead) {
		m_dead = true;
		m_health = 0.f;
		p_projectile->getOwner()->receiveExperience(m_expToPlayer);
	}
}

void Enemy::receiveTrapDamage(float p_damage)
{
	if (m_engineManager->getMasterClockSeconds() >= m_timeNextHitTrap) {
		m_health -= p_damage;
		m_timeNextHitTrap = m_engineManager->getMasterClockSeconds() + 0.15;
	}

	if (m_health < 0.f) {
		m_health = 0.f;
		m_dead = true;
	}
}

double Enemy::calculateDistance(Entity * p_posibleObjective)
{
	double t_posX = p_posibleObjective->getPositionX();
	double t_posY = p_posibleObjective->getPositionY();

	return sqrt(pow(m_posX - t_posX, 2) + pow(m_posY - t_posY, 2));
}

/*
	Search for the closest enemy if there are more than 1 and calculate the distance to the enemy.
	If not only calculate the distance to the enemy
*/
void Enemy::checkObjective()
{
	if (m_cooperativeMode) {
		float t_bestDistance = 10000;
		Player* t_bestObjective = nullptr;

		//Checks the closest enemy
		for (auto t_objective : ScreenGame::m_playerVector) {
			double t_distance = calculateDistance(t_objective);

			if (t_distance < t_bestDistance) {
				t_bestObjective = t_objective;
				t_bestDistance = t_distance;
			}
		}

		//sets best objective as objective
		m_objectivePlayer = t_bestObjective;
		m_distanceToObjective = t_bestDistance;
	}
	else {
		m_distanceToObjective = calculateDistance(m_objectivePlayer);
	}
	m_engineManager->getDirection(m_objectivePlayer->getPositionX(), m_objectivePlayer->getPositionY(), m_posX, m_posY, m_directionMoveX, m_directionMoveY);
}

void Enemy::move()
{
	m_posX = m_lastPosX + (m_deltaTime * m_velocity * m_directionMoveX);
	m_posY = m_lastPosY + (m_deltaTime * m_velocity * m_directionMoveY);
}

void Enemy::moveBackwards()
{
	m_posX = m_lastPosX + (m_deltaTime * m_velocity * -m_directionMoveX);
	m_posY = m_lastPosY + (m_deltaTime * m_velocity * -m_directionMoveY);
}

void Enemy::update(double p_time, double p_deltaTime)
{
	m_time = p_time;
	m_deltaTime = p_deltaTime;

	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	m_nearEntityVector = m_hashGrid->getNearby(this);

	if (!m_stunned) {
		checkObjective();
		move();
		atack();
	}
	else {
		if (m_engineManager->getMasterClockSeconds() >= m_endOfStun)
			m_stunned = false;
	}

	for (auto t_object : m_nearEntityVector) {
		if (t_object->getEntity() == Entities::TILE) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), m_spriteID)) {
				Tile* t_tile = dynamic_cast<Tile*>(t_object);
				t_tile->applyEffect(this);
			}
		}
	}
	updateAtack();

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
	m_healthBar->update(m_health / m_maxHealth, m_posX, m_posY);
}

void Enemy::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));
	
	if(m_health != m_maxHealth)
		m_healthBar->draw();
}

void Enemy::setStunned(float p_timeStunned)
{
	m_stunned = true;
	m_endOfStun = m_engineManager->getMasterClockSeconds() + p_timeStunned;
}
