#include "pch.h"
#include "projectileConus.h"
#include "projectileStraight.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"
#include "hashGrid.h"
#include "screenGame.h"

#include <iostream>


ProjectileConus::ProjectileConus(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage, bool p_crossEnemy, bool p_makeDamage) : Projectile(p_texturePath, p_ent, p_dir, p_playerPosX, p_playerPosY, p_damage)
{
	m_crossEnemy = p_crossEnemy;
	m_makeDamage = p_makeDamage;

	m_deleteOnCollide = false;
	m_makeInvisible = false;

	switch (p_dir)
	{
	case Direction::RIGHT:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::RIGHT_UP, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::RIGHT_DOWN, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		break;
	case Direction::LEFT:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::LEFT_UP, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::LEFT_DOWN, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		break;
	case Direction::UP:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::UP_RIGHT, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::UP_LEFT, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		break;
	case Direction::DOWN:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::DOWN_RIGHT, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::DOWN_LEFT, p_playerPosX, p_playerPosY, m_damage, p_crossEnemy, p_makeDamage);
		break;
	}
	ScreenGame::m_projectileVector.push_back(m_projectile1);
	ScreenGame::m_projectileVector.push_back(m_projectile2);
}


ProjectileConus::~ProjectileConus()
{
	if (m_projectile1 != nullptr) {
		delete m_projectile1;
		m_projectile1 = nullptr;
	}

	if (m_projectile2 != nullptr) {
		delete m_projectile2;
		m_projectile2 = nullptr;
	}
}

void ProjectileConus::update(double p_time, double p_deltaTime)
{
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	m_posX = m_lastPosX + (p_deltaTime * m_velocity * m_moveX);
	m_posY = m_lastPosY + (p_deltaTime * m_velocity * m_moveY);

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	if (m_projectile1 != nullptr) {
		m_projectile1->update(p_time, p_deltaTime);
		if (m_projectile1->getReadyToDelete()) {
			delete m_projectile1;
			m_projectile1 = nullptr;
		}

	}

	if (m_projectile2 != nullptr) {
		m_projectile2->update(p_time, p_deltaTime);
		if (m_projectile2->getReadyToDelete()) {
			delete m_projectile2;
			m_projectile2 = nullptr;
		}
	}

	if (m_makeInvisible && m_projectile1 == nullptr && m_projectile2 == nullptr)
		m_readyToDelete = true;

	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime)
		m_readyToDelete = true;

	m_nearEntityVector = m_hashGrid->getNearby(this);
	if (!m_makeInvisible) {
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
					else
						t_enemy->setStunned(5.f);

					if (!m_crossEnemy) {
						m_readyToDelete = true;
					}
				}
			}
		}
	}
	else {
		m_engineManager->getSprite(m_spriteID)->setScale(0, 0);
	}

}

void ProjectileConus::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(getSpriteID()));

	if (m_projectile1 != nullptr)
		m_projectile1->draw();

	if (m_projectile2 != nullptr)
		m_projectile2->draw();
}

