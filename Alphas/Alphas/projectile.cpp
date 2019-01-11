#include "pch.h"
#include "projectile.h"
#include "engineManager.h"
#include "hashGrid.h"
#include "screenGame.h"
#include "enemy.h"
#include "player.h"
#include "tile.h"


Projectile::Projectile(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage) : Entity(p_texturePath, p_ent)
{
	m_velocity = 600;
	m_lifeTime = 2.f;
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
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 4);
		break;
	case Direction::LEFT:
		m_moveX = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 4);
		break;
	case Direction::UP:
		m_moveY = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 5);
		break;
	case Direction::DOWN:
		m_moveY = 1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 5);
		break;
	case Direction::RIGHT_UP:
		m_moveX = 1;
		m_moveY = -t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 4);
		break;
	case Direction::RIGHT_DOWN:
		m_moveX = 1;
		m_moveY = t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 4);
		break;
	case Direction::LEFT_UP:
		m_moveX = -1;
		m_moveY = -t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 4);
		break;
	case Direction::LEFT_DOWN:
		m_moveX = -1;
		m_moveY = t_angle;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 4);
		break;
	case Direction::UP_RIGHT:
		m_moveX = t_angle;
		m_moveY = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 5);
		break;
	case Direction::UP_LEFT:
		m_moveX = -t_angle;
		m_moveY = -1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 5);
		break;
	case Direction::DOWN_RIGHT:
		m_moveX = t_angle;
		m_moveY = 1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 5);
		break;
	case Direction::DOWN_LEFT:
		m_moveX = -t_angle;
		m_moveY = 1;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 5);
		break;
	case Direction::NONE:
		if(p_ent != Entities::ENEMY_BOSS_BULLET)
			m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 4);
		break;
	}
}


Projectile::~Projectile()
{
	auto it = std::find(ScreenGame::m_projectileVector.begin(), ScreenGame::m_projectileVector.end(), this);
	ScreenGame::m_projectileVector.erase(it);
}

void Projectile::update(double p_time, double p_deltaTime){}

void Projectile::update()
{
	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime)
		m_readyToDelete = true;

	m_nearEntityVector = m_hashGrid->getNearby(this);
	if (m_entityOwner == Entities::BULLET_BLUE || m_entityOwner == Entities::BULLET_GREEN || m_entityOwner == Entities::BULLET_YELLOW) {
		//Player launch the projectile. If it collides with one block tile it will be destroyed.
		//If collides with enemy, enemy receive damage and projectile maybe or not be destroyed.
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
	else if (m_entityOwner == Entities::ENEMY_BULLET || m_entityOwner == Entities::ENEMY_BOSS_BULLET) {
		//Enemy launch the projectile. If it collides with one block tile it will be destroyed.
		//If collides with player, player receive damage and projectile maybe or not be destroyed.
		for (auto t_object : m_nearEntityVector) {
			if (t_object->getEntity() == Entities::TILE) {
				if (m_engineManager->checkCollision(t_object->getSpriteID(), m_spriteID))
					m_readyToDelete = true;
			}
			else if (t_object->getEntity() == Entities::PLAYER_BLUE || t_object->getEntity() == Entities::PLAYER_GREEN || t_object->getEntity() == Entities::PLAYER_YELLOW) {
				if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
					Player* t_player = dynamic_cast<Player*>(t_object);
					if (m_makeDamage)
						t_player->receiveDamage(m_damage, this);

					if (!m_crossEnemy) {
						m_readyToDelete = true;
					}
				}
			}
		}
	}
}

void Projectile::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(getSpriteID()));
}

void Projectile::setLifeTime(float p_lifeTime)
{
	m_lifeTime = p_lifeTime;
	m_dieTime = m_engineManager->getMasterClockSeconds() + m_lifeTime;
}
