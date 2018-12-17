#include "pch.h"
#include "projectileSpin.h"
#include "engineManager.h"
#include "player.h"

#include <iostream>
#include <math.h>


ProjectileSpin::ProjectileSpin(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_damage, Player* p_owner, bool p_crossEnemy, bool p_makeDamage) : Projectile(p_texturePath, p_ent, p_dir, p_owner->getPositionX(), p_owner->getPositionY(), p_damage)
{
	m_lifeTime = 5.f;
	m_dieTime = m_engineManager->getMasterClockSeconds() + m_lifeTime;

	m_crossEnemy = p_crossEnemy;
	m_makeDamage = p_makeDamage;

	//Increase m_angleStep ==> increase spinSpeed;
	m_angle = 0;
	m_angleStep = 0.1;
	m_radius = 50;

	m_owner = p_owner;

	if (m_makeDamage)
		p_owner->increaseArmor(5.f, 10.f);
	else
		p_owner->increaseSpeed(5.f, 2.f);
}


ProjectileSpin::~ProjectileSpin()
{
}


void ProjectileSpin::update(double p_time, double p_deltaTime)
{
	m_posX = m_owner->getPositionX() + (m_radius * cos(m_angle));
	m_posY = m_owner->getPositionY() + (m_radius * sin(m_angle));
	m_angle += m_angleStep;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	Projectile::update();
}