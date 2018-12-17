#include "pch.h"
#include "projectileSpinFixed.h"
#include "engineManager.h"
#include "screenGame.h"
#include "enemy.h"
#include "player.h"


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

	if (m_engineManager->getMasterClockSeconds() >= m_nextCheckTime) {
		m_nextCheckTime += 0.5f;

		//Check if the projectile collides with one enemy, if it collide it will be destroyed
		for (int i = 0; i < ScreenGame::m_enemyVector.size(); i++) {
			if (m_engineManager->checkCollisionCircle(ScreenGame::m_enemyVector[i]->getSpriteID()))
					ScreenGame::m_enemyVector[i]->receiveDamage(m_damage, this);
		}

		for (int i = 0; i < ScreenGame::m_playerVector.size(); i++) {
			if (m_engineManager->checkCollisionCircle(ScreenGame::m_playerVector[i]->getSpriteID()))
				ScreenGame::m_playerVector[i]->increaseHealth(m_damage);
		}
	}
}

void ProjectileSpinFixed::draw()
{
	m_engineManager->drawCircle();
	m_engineManager->draw(m_engineManager->getSprite(getSpriteID()));

}
