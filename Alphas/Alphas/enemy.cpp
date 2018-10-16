#include "pch.h"
#include "enemy.h"
#include "engineManager.h"
#include <iostream>


Enemy::Enemy(float p_posX, float p_posY, const char* p_path) : Entity(p_path, Entities::ENEMY)
{
	m_posX		= p_posX;
	m_posY		= p_posY;
	m_lastPosX	= p_posX;
	m_lastPosY	= p_posY;
	
	m_baseVelocity	= 75.f;
	m_velocity		= m_baseVelocity;
	m_maxHealth		= 100.f;
	m_health		= m_maxHealth;
	m_maxMana		= 100.f;
	m_mana			= m_maxMana;
	m_damage		= 25.f;
	m_atackSpeed	= 0.75f;
	m_dead			= false;
}


Enemy::~Enemy()
{
}

void Enemy::receiveDamage(float p_damage)
{
	m_health -= p_damage;
	std::cout << "Vida del enemigo: " << m_health << std::endl;
	if (m_health <= 0)
		m_dead = true;

}

void Enemy::update(float p_deltaTime)
{
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}
