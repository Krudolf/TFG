#include "pch.h"
#include "enemy.h"
#include "engineManager.h"
#include <iostream>


Enemy::Enemy(float p_posX, float p_posY, float p_velocity, const char* p_path) : Entity(p_path, Entities::ENEMY)
{
	m_posX		= p_posX;
	m_posY		= p_posY;
	m_lastPosX	= p_posX;
	m_lastPosY	= p_posY;
	
	m_velocity		= p_velocity;
	m_health		= 100.f;
	m_mana			= 100.f;
	m_damage		= 5.f;
	m_atackSpeed	= 0.75f;
	m_dead			= false;
}


Enemy::~Enemy()
{
}

void Enemy::receiveDamage(float p_damage)
{
	m_health -= p_damage;
	std::cout << m_health << std::endl;
	if (m_health <= 0)
		m_dead = true;

}

void Enemy::update(float p_deltaTime)
{
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}
