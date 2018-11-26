#include "pch.h"
#include "enemy.h"
#include "engineManager.h"
#include "game.h"
#include "player.h"

#include <iostream>


Enemy::Enemy(float p_posX, float p_posY, const char* p_path) : Entity(p_path, Entities::ENEMY)
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
	m_maxMana		= 100.f;
	m_mana			= m_maxMana;
	m_damage		= 25.f;
	m_atackSpeed	= 0.75f;
	m_dead			= false;

	m_cooperativeMode = Game::getCooperativeMode();
	m_distanceToObjective		= 1000;
	m_objectivePlayer = Game::m_playerVector[0];
}


Enemy::~Enemy()
{
}

void Enemy::receiveDamage(float p_damage)
{
	m_health -= p_damage;
	std::cout << "Vida del enemigo: " << m_health << std::endl;
	if (m_health <= 0)
		m_dead = true;

}

void Enemy::checkObjective()
{
	
	if (m_cooperativeMode) {
		float t_bestDistance = 1000;
		Player* t_bestObjective = nullptr;

		//Checks the closest enemy
		for (auto t_objective : Game::m_playerVector) {
			float t_distance = calculateDistance(t_objective);

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

float Enemy::calculateDistance(Player * p_posibleObjective)
{
	float t_posX = p_posibleObjective->getPositionX();
	float t_posY = p_posibleObjective->getPositionY();

	return sqrt(pow(m_posX - t_posX, 2) + pow(m_posY - t_posY, 2));
}

void Enemy::move()
{
	checkObjective();

	if (m_distanceToObjective >= 10) {
		m_posX = m_lastPosX + (m_deltaTime * m_velocity * m_directionMoveX);
		m_posY = m_lastPosY + (m_deltaTime * m_velocity * m_directionMoveY);
	}
}

void Enemy::moveBackwards()
{
	m_posX = m_lastPosX + (m_deltaTime * m_velocity * -m_directionMoveX);
	m_posY = m_lastPosY + (m_deltaTime * m_velocity * -m_directionMoveY);
}

void Enemy::goLastPosition()
{
	m_posX = m_lastPosX;
	m_posY = m_lastPosY;
}

void Enemy::update(double p_time, double p_deltaTime)
{
	m_deltaTime = p_deltaTime;

	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	move();

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}
