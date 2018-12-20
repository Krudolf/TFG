#include "pch.h"
#include "projectileSpinFixed.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"
#include "player.h"
#include "hashGrid.h"


ProjectileSpinFixed::ProjectileSpinFixed(const char* p_texturePath, Entities p_ent, Direction p_dir, float p_playerPosX, float p_playerPosY, float p_damage) : Projectile(p_texturePath, p_ent, p_dir, p_playerPosX, p_playerPosY, p_damage)
{
	m_lifeTime = 5.f;
	m_dieTime = m_engineManager->getMasterClockSeconds() + m_lifeTime;

	m_crossEnemy = true;
	m_makeDamage = false;

	//Increase m_angleStep ==> increase spinSpeed;
	m_angle = 0;
	m_angleStep = 0.1;
	m_radius = 150;
	m_nextCheckTime = m_engineManager->getMasterClockSeconds();

	m_centerPosX = p_playerPosX;
	m_centerPosY = p_playerPosY;

	m_engineManager->createCircle(m_centerPosX, m_centerPosY, m_radius);
}


ProjectileSpinFixed::~ProjectileSpinFixed()
{
}

void ProjectileSpinFixed::update(double p_time, double p_deltaTime)
{
	m_posX = m_centerPosX + (m_radius * cos(m_angle));
	m_posY = m_centerPosY + (m_radius * sin(m_angle));
	m_angle += m_angleStep;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

	//Check if life time end
	if (m_engineManager->getMasterClockSeconds() > m_dieTime)
		m_readyToDelete = true;


	/* 
		TODOO!:
		 - ESTE SE HA IDO AL TRASTE CON LAS COLISIONEEEEEES!! TENGO QUE VER SI PUEDO APAÑARLO O EN SU DEFECTO ME TOCARÁ VOLVER ATRAS A COMO ESTABA ANTES. 
	*/
	m_nearEntityVector = m_hashGrid->getNearby(this);
	if (m_engineManager->getMasterClockSeconds() >= m_nextCheckTime) {
		m_nextCheckTime += 0.5f;

		for (auto t_object : m_nearEntityVector) {
			if (t_object->getEntity() == Entities::ENEMY || t_object->getEntity() == Entities::ENEMY_BOSS) {
				if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
					Enemy* t_enemy = dynamic_cast<Enemy*>(t_object);
					t_enemy->receiveDamage(m_damage, this);
				}
			}
			else if (t_object->getEntity() == Entities::PLAYER_BLUE || t_object->getEntity() == Entities::PLAYER_GREEN || t_object->getEntity() == Entities::PLAYER_YELLOW) {
				if (m_engineManager->checkCollisionCircle(t_object->getSpriteID())) {
					Player* t_player = dynamic_cast<Player*>(t_object);
					t_player->increaseHealth(m_damage);
				}
			}
		}
	}
}

void ProjectileSpinFixed::draw()
{
	m_engineManager->drawCircle();
	m_engineManager->draw(m_engineManager->getSprite(getSpriteID()));

}
