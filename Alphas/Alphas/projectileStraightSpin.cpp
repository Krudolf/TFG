#include "pch.h"
#include "projectileStraightSpin.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"

#include <iostream>


ProjectileStraightSpin::ProjectileStraightSpin(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage) : Projectile(p_texturePath, p_ent, p_dir, p_playerPosX, p_playerPosY, p_damage)
{
	m_deleteOnCollide = false;
	m_straightPhase = true;
	m_spinPhase = false;

	m_angle = 0;
	m_angleStep = 0.1;
	m_radius = 50;
}


ProjectileStraightSpin::~ProjectileStraightSpin()
{
}

void ProjectileStraightSpin::update(double p_time, double p_deltaTime)
{
	if (m_straightPhase)
		updateStraight(p_deltaTime);
	else
		updateSpin();
}

void ProjectileStraightSpin::updateStraight(double p_deltaTime)
{
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	m_posX = m_lastPosX + (p_deltaTime * m_velocity * m_moveX);
	m_posY = m_lastPosY + (p_deltaTime * m_velocity * m_moveY);

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime) {
		m_readyToDelete = true;
	}

	//Check if the projectile collide with one enemy, if it collide change to spin mode
	for (int i = 0; i < ScreenGame::m_enemyVector.size(); i++) {
		if (m_engineManager->checkCollision(this->getSpriteID(), ScreenGame::m_enemyVector[i]->getSpriteID())) {
			ScreenGame::m_enemyVector[i]->receiveDamage(m_damage);
			
			m_straightPhase = false;
			m_spinPhase = true;
			
			m_spinPositionX = m_engineManager->getSprite(m_spriteID)->getPosition().x;
			m_spinPositionY = m_engineManager->getSprite(m_spriteID)->getPosition().y;
			
			m_dieTime = m_engineManager->getMasterClockSeconds() + 4;

			break;
		}
	}
}

void ProjectileStraightSpin::updateSpin()
{
	m_posX = m_spinPositionX + (m_radius * cos(m_angle));
	m_posY = m_spinPositionY + (m_radius * sin(m_angle));
	m_angle += m_angleStep;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	Projectile::update(m_deleteOnCollide);
}
