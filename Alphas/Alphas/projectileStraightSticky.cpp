#include "pch.h"
#include "projectileStraightSticky.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"
#include "player.h"
#include "hashGrid.h"
#include "tile.h"


ProjectileStraightSticky::ProjectileStraightSticky(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_entityPosX, float p_entityPosY, float p_damage) : Projectile(p_texturePath, p_ent, p_dir, p_entityPosX, p_entityPosY, p_damage)
{
	m_crossEnemy = false;
	m_makeDamage = true;

	m_straightPhase = true;

	m_angle = 0;
	m_angleStep = 0.1;
	m_radius = 50;

	m_enemySticky	= nullptr;
	m_playerSticky	= nullptr;
}


ProjectileStraightSticky::~ProjectileStraightSticky()
{
}

void ProjectileStraightSticky::update(double p_time, double p_deltaTime)
{
	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() >= m_dieTime){
		m_readyToDelete = true;
		if (m_enemySticky != nullptr)
			m_enemySticky->setSticky(false);
	}
	else {
		m_nearEntityVector = m_hashGrid->getNearby(this);
		if (m_straightPhase)
			updateStraight(p_deltaTime);
		else
			updateSpin();
	}
}

void ProjectileStraightSticky::updateStraight(double p_deltaTime)
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
		else if (t_object->getEntity() == Entities::ENEMY ||t_object->getEntity() == Entities::ENEMY_BOSS) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
				Enemy* t_enemy = dynamic_cast<Enemy*>(t_object);

				m_straightPhase = false;

				m_enemySticky = t_enemy;
				m_enemySticky->setSticky(true);
				m_enemySticky->receiveDamage(m_damage, this);

				m_dieTime = m_engineManager->getMasterClockSeconds() + 5;
			}
		}
		else if (t_object->getEntity() == Entities::PLAYER_BLUE || t_object->getEntity() == Entities::PLAYER_YELLOW) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
				Player* t_player = dynamic_cast<Player*>(t_object);
				m_straightPhase = false;

				m_playerSticky = t_player;
				m_playerSticky->increaseArmor(5, 10);
				m_playerSticky->increaseHealth(m_damage);

				m_dieTime = m_engineManager->getMasterClockSeconds() + 5;
			}
		}
	}
}

void ProjectileStraightSticky::updateSpin()
{
	if (m_enemySticky != nullptr) {
		m_posX = m_enemySticky->getPositionX() + (m_radius * cos(m_angle));
		m_posY = m_enemySticky->getPositionY() + (m_radius * sin(m_angle));
		m_enemySticky->receiveDamage(m_damage*0.75, this);
	}
	else if (m_playerSticky != nullptr) {
		m_posX = m_playerSticky->getPositionX() + (m_radius * cos(m_angle));
		m_posY = m_playerSticky->getPositionY() + (m_radius * sin(m_angle));
	}
	m_angle += m_angleStep;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	//Check if the projectile collides with one enemy, if it collide it will be destroyed
	for (auto t_object : m_nearEntityVector) {
		if (t_object->getEntity() == Entities::ENEMY || t_object->getEntity() == Entities::ENEMY_BOSS) {
			if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
				Enemy* t_enemy = dynamic_cast<Enemy*>(t_object);

				t_enemy->receiveDamage(m_damage, this);
			}
		}
	}
}
