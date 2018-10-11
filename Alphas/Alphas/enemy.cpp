#include "pch.h"
#include "enemy.h"
#include "engineManager.h"
#include <iostream>


Enemy::Enemy(float p_posX, float p_posY, float p_velocity, const char* p_path) : Entity(p_path, Entities::ENEMY)
{
	m_posX = p_posX;
	m_posY = p_posY;
	m_lastPosX = p_posX;
	m_lastPosY = p_posY;
	m_velocity = p_velocity;
}


Enemy::~Enemy()
{
	std::cout << "BORRAMOS ENEMY" << std::endl;
}

void Enemy::update(float p_deltaTime)
{
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);

}
