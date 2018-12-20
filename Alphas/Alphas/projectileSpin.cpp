#include "pch.h"
#include "projectileSpin.h"
#include "engineManager.h"
#include "player.h"
#include "enemy.h"
#include "hashGrid.h"
#include <math.h>


ProjectileSpin::ProjectileSpin(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_damage, Player* p_owner, bool p_crossEnemy, bool p_makeDamage) : Projectile(p_texturePath, p_ent, p_dir, p_owner->getPositionX(), p_owner->getPositionY(), p_damage)
{
	m_lifeTime = 5.f;
	m_dieTime = m_engineManager->getMasterClockSeconds() + m_lifeTime;

	m_crossEnemy = p_crossEnemy;
	m_makeDamage = p_makeDamage;

	//Increase m_angleStep ==> increase spinSpeed;
	m_angle = 0;
	m_angleStep = 0.25;
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

	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime)
		m_readyToDelete = true;

	m_nearEntityVector = m_hashGrid->getNearby(this);
	if (m_entityOwner == Entities::BULLET_BLUE || m_entityOwner == Entities::BULLET_GREEN || m_entityOwner == Entities::BULLET_YELLOW) {
		//Player launch the projectile. If it collides with one block tile it will be destroyed.
		//If collides with enemy, enemy receive damage and projectile maybe or not be destroyed.
		for (auto t_object : m_nearEntityVector) {
			if (t_object->getEntity() == Entities::ENEMY || t_object->getEntity() == Entities::ENEMY_BOSS) {
				if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
					Enemy* t_enemy = dynamic_cast<Enemy*>(t_object);
					if (m_makeDamage)
						t_enemy->receiveDamage(m_damage, this);
					else
						t_enemy->setStunned(5.f);

					if (!m_crossEnemy) {
						m_readyToDelete = true;
					}
				}
			}
		}
	}
}