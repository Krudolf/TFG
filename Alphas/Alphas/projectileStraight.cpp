#include "pch.h"
#include "projectileStraight.h"
#include "engineManager.h"

#include <iostream>


ProjectileStraight::ProjectileStraight(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_entityPosX, float p_entityPosY, float p_damage) : Projectile(p_texturePath, p_ent, p_dir, p_entityPosX, p_entityPosY, p_damage)
{
	m_deleteOnCollide = true;
}

ProjectileStraight::ProjectileStraight(const char * p_texturePath, Entities p_ent, float p_entityPosX, float p_entityPosY, float p_damage, float p_dirX, float p_dirY) : Projectile(p_texturePath, p_ent, Direction::NONE, p_entityPosX, p_entityPosY, p_damage)
{
	m_deleteOnCollide = true;
	m_moveX = p_dirX;
	m_moveY = p_dirY;
	m_velocity *= 1.5;
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
