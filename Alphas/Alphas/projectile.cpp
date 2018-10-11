#include "pch.h"
#include "projectile.h"
#include "engineManager.h"

#include <iostream>


Projectile::Projectile(int p_textureID, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY) : Entity(p_textureID, p_ent)
{
	m_lifeTime = 2.5f;
	m_dieTime = m_engineManager->getMasterClockSeconds() + m_lifeTime;
	m_readyToDelete = false;

	m_moveX = 0;
	m_moveY = 0;

	m_posX = p_playerPosX;
	m_posY = p_playerPosY;

	switch (p_dir)
	{
	case Direction::RIGHT:
		m_moveX = 1;
		break;
	case Direction::LEFT:
		m_moveX = -1;
		break;
	case Direction::UP:
		m_moveY = -1;
		break;
	case Direction::DOWN:
		m_moveY = 1;
		break;
	}
}


Projectile::~Projectile()
{
}

void Projectile::update(float p_deltaTime)
{
	if (m_engineManager->getMasterClockSeconds() > m_dieTime) {
		m_readyToDelete = true;
	}
	
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;
	m_posX = m_lastPosX + p_deltaTime * m_velocity * m_moveX;
	m_posY = m_lastPosY + p_deltaTime * m_velocity * m_moveY;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}
