#include "pch.h"
#include "projectileStraightStun.h"
#include "engineManager.h"
#include "enemy.h"
#include "screenGame.h"


ProjectileStraightStun::ProjectileStraightStun(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_entityPosX, float p_entityPosY, float p_damage, bool p_crossEnemy, bool p_makeDamage) : Projectile(p_texturePath, p_ent, p_dir, p_entityPosX, p_entityPosY, p_damage)
{
	m_crossEnemy = p_crossEnemy;
	m_makeDamage = p_makeDamage;

	m_direction = p_dir;
}


ProjectileStraightStun::~ProjectileStraightStun()
{
}

void ProjectileStraightStun::update(double p_time, double p_deltaTime)
{
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	m_posX = m_lastPosX + (p_deltaTime * m_velocity * m_moveX);
	m_posY = m_lastPosY + (p_deltaTime * m_velocity * m_moveY);

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime)
		m_readyToDelete = true;

	//Check if the projectile collides with one enemy, if it collide it will be destroyed
	for (auto t_object : m_nearEntityVector) {
		if (t_object->getEntity() == Entities::TILE) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), m_spriteID))
				m_readyToDelete = true;
		}
		else if (t_object->getEntity() == Entities::ENEMY || t_object->getEntity() == Entities::ENEMY_BOSS) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
				Enemy* t_enemy = dynamic_cast<Enemy*>(t_object);
				if (m_makeDamage)
					t_enemy->receiveDamage(m_damage, this);
			
				t_enemy->setStunned(5.f);

				if (!m_crossEnemy) {
					m_readyToDelete = true;
				}
			}
		}
	}
}
