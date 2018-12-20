#include "pch.h"
#include "projectileStraightSpin.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"
#include "player.h"
#include "hashGrid.h"
#include "tile.h"


ProjectileStraightSpin::ProjectileStraightSpin(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage, Player* p_owner) : Projectile(p_texturePath, p_ent, p_dir, p_playerPosX, p_playerPosY, p_damage)
{
	m_owner = p_owner;

	m_crossEnemy = true;
	m_makeDamage = true;

	m_straightPhase = true;

	m_angle = 0;
	m_angleStep = 0.25;
	m_radius = 50;
}


ProjectileStraightSpin::~ProjectileStraightSpin()
{
}

void ProjectileStraightSpin::update(double p_time, double p_deltaTime)
{
	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() >= m_dieTime)
		m_readyToDelete = true;
	else {
		m_nearEntityVector = m_hashGrid->getNearby(this);
		if (m_straightPhase)
			updateStraight(p_deltaTime);
		else
			updateSpin();
	}
}

void ProjectileStraightSpin::updateStraight(double p_deltaTime)
{
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	m_posX = m_lastPosX + (p_deltaTime * m_velocity * m_moveX);
	m_posY = m_lastPosY + (p_deltaTime * m_velocity * m_moveY);

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	//Check if the projectile collide with one enemy, if it collide change to spin mode
	for (auto t_object : m_nearEntityVector) {
		if (t_object->getEntity() == Entities::TILE) {
			if (m_engineManager->checkCollision(m_spriteID, t_object->getSpriteID())) {
				Tile* t_tile = dynamic_cast<Tile*>(t_object);
				t_tile->applyEffect(this);
			}
		}
		else if (t_object->getEntity() == Entities::ENEMY || t_object->getEntity() == Entities::ENEMY_BOSS) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
				Enemy* t_enemy = dynamic_cast<Enemy*>(t_object);
				t_enemy->receiveDamage(m_damage, this);
					
				m_straightPhase = false;
			
				m_spinPositionX = m_engineManager->getSprite(m_spriteID)->getPosition().x;
				m_spinPositionY = m_engineManager->getSprite(m_spriteID)->getPosition().y;
			
				m_dieTime = m_engineManager->getMasterClockSeconds() + 4;
			}
		}
	}
}

void ProjectileStraightSpin::updateSpin()
{
	m_posX = m_spinPositionX + (m_radius * cos(m_angle));
	m_posY = m_spinPositionY + (m_radius * sin(m_angle));
	m_angle += m_angleStep;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	//Check if the projectile collides with one enemy, if it collide it will be destroyed
	for (auto t_object : m_nearEntityVector) {
		if (t_object->getEntity() == Entities::ENEMY || t_object->getEntity() == Entities::ENEMY_BOSS) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
				Enemy* t_enemy = dynamic_cast<Enemy*>(t_object);
				
				//if (m_makeDamage)
				t_enemy->receiveDamage(m_damage, this);
				m_owner->increaseMana(m_damage / 100);
			}
		}
	}
}
