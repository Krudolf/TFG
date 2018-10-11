#include "pch.h"
#include "player.h"
#include "engineManager.h"
#include "projectile.h"

#include <iostream>

Player::Player(float p_posX, float p_posY, float p_velocity, const char* p_path) : Entity(p_path, Entities::PLAYER1)
{
	m_posX		= p_posX;
	m_posY		= p_posY;
	m_lastPosX	= p_posX;
	m_lastPosY	= p_posY;
	m_velocity	= p_velocity;

	m_health		= 100.f;
	m_mana			= 100.f;
	m_damage		= 10.f;
	m_atackSpeed	= 0.25f;

	m_basicInCooldown = false;
	m_nextBasic = m_engineManager->getMasterClockSeconds();
}


Player::~Player()
{
	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		delete m_basicProjectiles[i];
		m_basicProjectiles[i] = nullptr;
	}
	m_basicProjectiles.clear();
}


void Player::move() {
	int t_sprint = 1;
	
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		t_sprint = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_posX = m_lastPosX + m_deltaTime * m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 2);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_posX = m_lastPosX + m_deltaTime * -m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 3);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_posY = m_lastPosY + m_deltaTime * m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_posY = m_lastPosY + m_deltaTime * -m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	}
	
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}

void Player::rangeAtack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 2);
		launchProjectile(Direction::RIGHT);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 3);
		launchProjectile(Direction::LEFT);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		launchProjectile(Direction::DOWN);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		launchProjectile(Direction::UP);
	}
}

void Player::launchProjectile(Direction p_dir)
{
	if (!m_basicInCooldown && m_basicProjectiles.size() < m_maxProjectiles) {
		m_basicInCooldown = true;
		m_nextBasic = m_engineManager->getMasterClockSeconds() + m_atackSpeed;

		Projectile* t_projectile = new Projectile(m_textureID, Entities::BULLET1, p_dir, m_posX, m_posY, m_damage);
		m_basicProjectiles.push_back(t_projectile);
	}
}

void Player::updateBasicAtack()
{
	float t_time = m_engineManager->getMasterClockSeconds();
	if (t_time > m_nextBasic)
		m_basicInCooldown = false;

	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		m_basicProjectiles[i]->update(m_deltaTime);

		if (m_basicProjectiles[i]->getReadyToDelete()) {
			delete m_basicProjectiles[i];
			m_basicProjectiles.erase(m_basicProjectiles.begin() + i);
		}
	}
}

void Player::update(float p_deltaTime) {
	m_deltaTime = p_deltaTime;

	updateBasicAtack();
	move();
	rangeAtack();
}

void Player::draw()
{
	m_engineManager->getWindow()->draw(*m_engineManager->getSprite(m_spriteID));

	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		m_engineManager->getWindow()->draw(*m_engineManager->getSprite(m_basicProjectiles[i]->getSpriteID()));
	}
}