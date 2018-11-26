#include "pch.h"
#include "player.h"
#include "engineManager.h"
#include "projectile.h"
#include "projectileStraight.h"
#include "projectileSpin.h"
#include "projectileStraightSpin.h"
#include "projectileConus.h"
#include "game.h"
#include "potion.h"

#include <iostream>

Player::Player(float p_posX, float p_posY, const char* p_path) : Entity(p_path, Entities::PLAYER1)
{
	m_posX		= p_posX;
	m_posY		= p_posY;
	m_lastPosX	= p_posX;
	m_lastPosY	= p_posY;
	
	m_baseVelocity	= 100.f;
	m_velocity		= m_baseVelocity;
	m_maxHealth		= 100.f;
	m_health		= m_maxHealth;
	m_maxMana		= 100.f;
	m_mana			= m_maxMana;
	m_damage		= 1.f;
	m_atackSpeed	= 0.25f;

	m_speedPotionEfect = false;

	m_faceDirection = Direction::RIGHT;

	m_basicInCooldown = false;
	m_nextBasic = m_engineManager->getMasterClockSeconds();

	m_hability1Launched = false;
	m_hability2Launched = false;
	m_hability3Launched = false;
	m_hability4Launched = false;
}


Player::~Player()
{
	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		delete m_basicProjectiles[i];
		m_basicProjectiles[i] = nullptr;
	}
	m_basicProjectiles.clear();
}

void Player::increaseHealth(float p_health)
{
	m_health += p_health;
	std::cout << "Health: " <<  m_health << std::endl;
}

void Player::increaseMana(float p_mana)
{
	m_mana += p_mana;
	std::cout << "Mana: " << m_mana << std::endl;
}

void Player::increaseSpeed(float p_duration)
{
	if (!m_speedPotionEfect) {
		m_speedPotionEfect = true;
		m_endOfSpeedPotionEffect = m_engineManager->getMasterClockSeconds() + p_duration;
		m_velocity += 50;
	}
	else {
		m_endOfSpeedPotionEffect = m_engineManager->getMasterClockSeconds() + p_duration;
	}
}


void Player::move() {
	int t_sprint = 1;
	
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		t_sprint = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_faceDirection = Direction::RIGHT;
		m_posX = m_lastPosX + (m_deltaTime * m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_faceDirection = Direction::LEFT;
		m_posX = m_lastPosX + (m_deltaTime * -m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 3);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_faceDirection = Direction::DOWN;
		m_posY = m_lastPosY + (m_deltaTime * m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_faceDirection = Direction::UP;
		m_posY = m_lastPosY + (m_deltaTime * -m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	}
	
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}

void Player::rangeAtack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_faceDirection = Direction::RIGHT;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 2);
		launchProjectile(m_faceDirection, ProjectileType::STRAIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_faceDirection = Direction::LEFT;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 3);
		launchProjectile(m_faceDirection, ProjectileType::STRAIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_faceDirection = Direction::DOWN;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		launchProjectile(m_faceDirection, ProjectileType::STRAIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_faceDirection = Direction::UP;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		launchProjectile(m_faceDirection, ProjectileType::STRAIGHT);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !m_hability1Launched) {
		hability1();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !m_hability2Launched) {
		hability2();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !m_hability3Launched) {
		hability3();
	}
}

void Player::hability1()
{
	m_hability1Launched = true;
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	m_hability1 = new ProjectileSpin(m_texturePath, Entities::BULLET1, Direction::NONE, m_posX, m_posY, m_damage / 10, this);
}

void Player::hability2()
{
	m_hability2Launched = true;
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	m_hability2 = new ProjectileStraightSpin(m_texturePath, Entities::BULLET1, m_faceDirection, m_posX, m_posY, m_damage);
}

void Player::hability3()
{
	m_hability3Launched = true;
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	m_hability3 = new ProjectileConus(m_texturePath, Entities::BULLET1, m_faceDirection, m_posX, m_posY, m_damage);
}

void Player::hability4()
{
}

void Player::launchProjectile(Direction p_dir, ProjectileType p_projectileType)
{
	if (!m_basicInCooldown && m_basicProjectiles.size() < m_maxProjectiles) {
		m_basicInCooldown = true;
		m_nextBasic = m_engineManager->getMasterClockSeconds() + m_atackSpeed;

		Projectile* t_projectile = new ProjectileStraight(m_texturePath, Entities::BULLET1, p_dir, m_posX, m_posY, m_damage);

		m_basicProjectiles.push_back(t_projectile);
		Game::m_entityVector.push_back(t_projectile);
	}
}

void Player::pickObject()
{
	for (int i = 0; i < Game::m_potionVector.size(); i++) {
		if (m_engineManager->checkCollision(this->m_spriteID, Game::m_potionVector[i]->getSpriteID())) {
			Game::m_potionVector[i]->setEffect(this);
		}
	}
}

void Player::updateBasicAtack()
{
	float t_time = m_engineManager->getMasterClockSeconds();
	if (t_time > m_nextBasic)
		m_basicInCooldown = false;

	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		m_basicProjectiles[i]->update(m_time, m_deltaTime);

		if (m_basicProjectiles[i]->getReadyToDelete()) {
			//Delete the projectile from the game vector
			auto it = std::find(Game::m_entityVector.begin(), Game::m_entityVector.end(), m_basicProjectiles[i]);
			Game::m_entityVector.erase(it);

			//Delete the projectile from the player vector os projectiles
			delete m_basicProjectiles[i];
			m_basicProjectiles.erase(m_basicProjectiles.begin() + i);
		}
	}
}

void Player::updatePotionEffects()
{
	float t_currentTime = m_engineManager->getMasterClockSeconds();
	if (m_speedPotionEfect && t_currentTime >= m_endOfSpeedPotionEffect) {
		m_speedPotionEfect = false;
		m_velocity = m_baseVelocity;
	}
}

void Player::update(double p_time, double p_deltaTime) {
	m_time		= p_time;
	m_deltaTime = p_deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		pickObject();

	updatePotionEffects();
	updateBasicAtack();
	move();
	rangeAtack();

	if (m_hability1Launched) {
		m_hability1->update(m_time, m_deltaTime);
		if (m_hability1->getReadyToDelete()) {
			delete m_hability1;
			m_hability1 = nullptr;
			m_hability1Launched = false;
		}
	}

	if (m_hability2Launched) {
		m_hability2->update(m_time, m_deltaTime);
		if (m_hability2->getReadyToDelete()) {
			delete m_hability2;
			m_hability2 = nullptr;
			m_hability2Launched = false;
		}
	}

	if (m_hability3Launched) {
		m_hability3->update(m_time, m_deltaTime);
		if (m_hability3->getReadyToDelete()) {
			delete m_hability3;
			m_hability3 = nullptr;
			m_hability3Launched = false;
		}
	}
}

void Player::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));

	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		m_basicProjectiles[i]->draw();
	}

	if (m_hability1Launched)
		m_hability1->draw();

	if (m_hability2Launched)
		m_hability2->draw();

	if (m_hability3Launched)
		m_hability3->draw();
}