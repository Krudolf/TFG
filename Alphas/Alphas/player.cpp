#include "pch.h"
#include "player.h"
#include "engineManager.h"

#include <iostream>

Player::Player() : Entity()
{
	m_velocity = 100;
}


Player::~Player()
{

}


void Player::move(float p_deltaTime) {
	int t_sprint = 1;
	
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		t_sprint = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_posX = m_lastPosX + p_deltaTime * m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, 0, 2);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_posX = m_lastPosX + p_deltaTime * -m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, 0, 3);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_posY = m_lastPosY + p_deltaTime * m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, 0, 0);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_posY = m_lastPosY + p_deltaTime * -m_velocity * t_sprint;
		m_engineManager->setSpriteFrame(m_spriteID, 0, 1);
	}
	
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}


void Player::update(float p_deltaTime) {
	move(p_deltaTime);
}