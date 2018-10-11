#include "pch.h"
#include "projectile.h"
#include "engineManager.h"
#include "game.h"
#include "enemy.h"

#include <iostream>


Projectile::Projectile(int p_textureID, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage) : Entity(p_textureID, p_ent)
{
	m_lifeTime = 2.5f;
	m_dieTime = m_engineManager->getMasterClockSeconds() + m_lifeTime;
	m_readyToDelete = false;

	m_posX = p_playerPosX;
	m_posY = p_playerPosY;
	
	m_damage = p_damage;

	m_moveX = 0;
	m_moveY = 0;
	switch (p_dir)
	{
	case Direction::RIGHT:
		m_moveX = 1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		break;
	case Direction::LEFT:
		m_moveX = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		break;
	case Direction::UP:
		m_moveY = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		break;
	case Direction::DOWN:
		m_moveY = 1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		break;
	}
}


Projectile::~Projectile()
{
}

void Projectile::update(float p_deltaTime)
{
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;
	m_posX = m_lastPosX + p_deltaTime * m_velocity * m_moveX;
	m_posY = m_lastPosY + p_deltaTime * m_velocity * m_moveY;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime)
		m_readyToDelete = true;

	//Check if the projectile collide with one enemy, if it collide it will be destroyed
	for (int i = 0; i < Game::m_enemyVector.size(); i++) {
		if (m_engineManager->checkCollision(this->getSpriteID(), Game::m_enemyVector[i]->getSpriteID())) {
			Game::m_enemyVector[i]->receiveDamage(m_damage);
			m_readyToDelete = true;
			break;
		}
	}
}
