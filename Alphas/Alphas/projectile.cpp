#include "pch.h"
#include "projectile.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"
#include "player.h"

#include <iostream>


Projectile::Projectile(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage) : Entity(p_texturePath, p_ent)
{
	m_velocity = 400;
	m_lifeTime = 2.5f;
	m_dieTime = m_engineManager->getMasterClockSeconds() + m_lifeTime;
	m_readyToDelete = false;

	m_posX = p_playerPosX;
	m_posY = p_playerPosY;
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;
	
	m_damage = p_damage;

	m_entityOwner = p_ent;

	m_moveX = 0;
	m_moveY = 0;
	float t_angle = 0.33;
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
	case Direction::RIGHT_UP:
		m_moveX = 1;
		m_moveY = -t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		break;
	case Direction::RIGHT_DOWN:
		m_moveX = 1;
		m_moveY = t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		break;
	case Direction::LEFT_UP:
		m_moveX = -1;
		m_moveY = -t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		break;
	case Direction::LEFT_DOWN:
		m_moveX = -1;
		m_moveY = t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		break;
	case Direction::UP_RIGHT:
		m_moveX = t_angle;
		m_moveY = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		break;
	case Direction::UP_LEFT:
		m_moveX = -t_angle;
		m_moveY = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		break;
	case Direction::DOWN_RIGHT:
		m_moveX = t_angle;
		m_moveY = 1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		break;
	case Direction::DOWN_LEFT:
		m_moveX = -t_angle;
		m_moveY = 1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		break;
	case Direction::NONE:
		//m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		break;
	}
}


Projectile::~Projectile()
{
}

void Projectile::update(double p_time, double p_deltaTime){}

void Projectile::update(bool p_deleteOnCollide)
{
	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime)
		m_readyToDelete = true;

	if (m_entityOwner == Entities::BULLET1 || m_entityOwner == Entities::BULLET2) {
		//Check if the projectile collides with one enemy, if it collide it will be destroyed
		for (int i = 0; i < ScreenGame::m_enemyVector.size(); i++) {
			if (m_engineManager->checkCollision(this->getSpriteID(), ScreenGame::m_enemyVector[i]->getSpriteID())) {
				ScreenGame::m_enemyVector[i]->receiveDamage(m_damage);

				if (p_deleteOnCollide) {
					m_readyToDelete = true;
				}

				break;
			}
		}
	}
	else if (m_entityOwner == Entities::ENEMY_BULLET || m_entityOwner == Entities::ENEMY_BOSS_BULLET) {
		//Check if the projectile collides with one player, if it collide it will be destroyed
		for (int i = 0; i < ScreenGame::m_playerVector.size(); i++) {
			if (m_engineManager->checkCollision(this->getSpriteID(), ScreenGame::m_playerVector[i]->getSpriteID())) {
				ScreenGame::m_playerVector[i]->receiveDamage(m_damage);

				if (p_deleteOnCollide) {
					m_readyToDelete = true;
				}

				break;
			}
		}
	}
}

void Projectile::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(getSpriteID()));
}
