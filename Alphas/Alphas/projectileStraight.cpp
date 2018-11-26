#include "pch.h"
#include "projectileStraight.h"
#include "engineManager.h"

#include <iostream>


ProjectileStraight::ProjectileStraight(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage) : Projectile(p_texturePath, p_ent, p_dir, p_playerPosX, p_playerPosY, p_damage)
{
	m_deleteOnCollide = true;
}


ProjectileStraight::~ProjectileStraight()
{
}

void ProjectileStraight::update(double p_time, double p_deltaTime)
{
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	m_posX = m_lastPosX + (p_deltaTime * m_velocity * m_moveX);
	m_posY = m_lastPosY + (p_deltaTime * m_velocity * m_moveY);

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	Projectile::update(m_deleteOnCollide);
}
