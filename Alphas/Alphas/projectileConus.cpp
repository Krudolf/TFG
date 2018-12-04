#include "pch.h"
#include "projectileConus.h"
#include "projectileStraight.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"

#include <iostream>


ProjectileConus::ProjectileConus(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage) : Projectile(p_texturePath, p_ent, p_dir, p_playerPosX, p_playerPosY, p_damage)
{
	m_deleteOnCollide = false;
	m_makeInvisible = false;

	switch (p_dir)
	{
	case Direction::RIGHT:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::RIGHT_UP, p_playerPosX, p_playerPosY, m_damage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::RIGHT_DOWN, p_playerPosX, p_playerPosY, m_damage);
		break;
	case Direction::LEFT:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::LEFT_UP, p_playerPosX, p_playerPosY, m_damage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::LEFT_DOWN, p_playerPosX, p_playerPosY, m_damage);
		break;
	case Direction::UP:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::UP_RIGHT, p_playerPosX, p_playerPosY, m_damage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::UP_LEFT, p_playerPosX, p_playerPosY, m_damage);
		break;
	case Direction::DOWN:
		m_projectile1 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::DOWN_RIGHT, p_playerPosX, p_playerPosY, m_damage);
		m_projectile2 = new ProjectileStraight(m_texturePath, m_entityOwner, Direction::DOWN_LEFT, p_playerPosX, p_playerPosY, m_damage);
		break;
	}
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

	if (!m_makeInvisible) {
		//Check if the projectile collide with one enemy, if it collide it will be destroyed
		for (int i = 0; i < ScreenGame::m_enemyVector.size(); i++) {
			if (m_engineManager->checkCollision(this->getSpriteID(), ScreenGame::m_enemyVector[i]->getSpriteID())) {
				ScreenGame::m_enemyVector[i]->receiveDamage(m_damage);
				m_makeInvisible = true;

				break;
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

