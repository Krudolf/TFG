#include "pch.h"
#include "player.h"
#include "engineManager.h"
#include "projectile.h"
#include "projectileStraight.h"
#include "projectileSpin.h"
#include "projectileStraightSpin.h"
#include "projectileConus.h"
#include "screenGame.h"
#include "potion.h"
#include "hashGrid.h"
#include "tile.h"
#include "joystick_enum.h"


Player::Player(float p_posX, float p_posY, const char* p_path, Entities p_playerEntity) : Entity(p_path, p_playerEntity)
{
	m_posX		= p_posX;
	m_posY		= p_posY;
	m_lastPosX	= p_posX;
	m_lastPosY	= p_posY;

	m_keyboard = true;

	m_level = 3;
	m_baseExperience = 25.f;
	m_experienceFactor = 2.5f;
	m_currentExperience = 0.f;
	m_topExperience = m_baseExperience + (pow((m_level + 1), m_experienceFactor));

	m_alive = true;
	m_pasiveActive = false;
	m_nearPotion = false;

	m_speedPotionEfect		= false;
	m_damagePotionEfect		= false;
	m_armorPotionEfect		= false;
	m_atackSpeedPotionEfect	= false;

	m_endOfSpeedPotionEffect		= 0.0f;
	m_endOfDamagePotionEffect		= 0.0f;
	m_endOfArmorPotionEffect		= 0.0f;
	m_endOfAtackSpeedPotionEffect	= 0.0f;

	m_faceDirection = Direction::RIGHT;

	m_basicInCooldown = false;
	m_nextBasic = m_engineManager->getMasterClockSeconds();

	m_hability1Launched = false;
	m_hability2Launched = false;
	m_hability3Launched = false;

	m_hability1EnoughMana = true;
	m_hability2EnoughMana = true;
	m_hability3EnoughMana = true;

	m_hability1CooldownDuration = 5.f;
	m_hability2CooldownDuration = 5.f;
	m_hability3CooldownDuration = 5.f;

	m_hability1ActivationTime = 0.f;
	m_hability2ActivationTime = 0.f;
	m_hability3ActivationTime = 0.f;

	m_lastProjectile = nullptr;
	m_timeNextHitProjectile = 0.f;
	m_timeNextHitTrap = 0.f;
}


Player::~Player()
{

	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		delete m_basicProjectiles[i];
		m_basicProjectiles[i] = nullptr;
	}
	m_basicProjectiles.clear();
	
	//delete m_actions;
	//m_actions = nullptr;
}

void Player::receiveDamage(float p_damage)
{
	float t_blockDamage = p_damage * (m_armor / 100);
	m_health -= (p_damage - t_blockDamage);

	if (m_health < 0.f) {
		m_health = 0.f;
		m_alive = false;
	}
}

void Player::receiveDamage(float p_damage, Projectile* p_projectile)
{
	if (m_lastProjectile != p_projectile) {
		float t_blockDamage = p_damage * (m_armor / 100);
		m_health -= (p_damage - t_blockDamage);
		m_lastProjectile = p_projectile;
		m_timeNextHitProjectile = m_engineManager->getMasterClockSeconds() + 0.15;
	}
	else {
		if (m_engineManager->getMasterClockSeconds() >= m_timeNextHitProjectile) {
			float t_blockDamage = p_damage * (m_armor / 100);
			m_health -= (p_damage - t_blockDamage);
			m_timeNextHitProjectile = m_engineManager->getMasterClockSeconds() + 0.15;
		}
	}

	if (m_health < 0.f) {
		m_health = 0.f;
		m_alive = false;
	}
}

void Player::receiveTrapDamage(float p_damage)
{
	if (m_engineManager->getMasterClockSeconds() >= m_timeNextHitTrap) {
		m_health -= p_damage;
		m_timeNextHitTrap = m_engineManager->getMasterClockSeconds() + 0.15;
	}

	if (m_health < 0.f) {
		m_health = 0.f;
		m_alive = false;
	}
}

void Player::receiveExperience(float p_experience)
{
	m_currentExperience += p_experience;

	if (m_currentExperience >= m_topExperience) {
		m_level++;
		levelStats();
		m_currentExperience -= m_topExperience;
		m_topExperience = m_baseExperience + (pow((m_level + 1), m_experienceFactor));
	}
}

bool Player::enoughMana(float p_mana)
{
	if (m_mana >= p_mana) {
		m_mana -= p_mana;
		return true;
	}
	else
		return false;
}

void Player::increaseHealth(float p_health)
{
	m_health += p_health;

	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
}

void Player::increaseMana(float p_mana)
{
	m_mana += p_mana;

	if (m_mana > m_maxMana)
		m_mana = m_maxMana;
}

void Player::increaseSpeed(float p_duration, float p_speedIncrease)
{
	m_speedPotionEfect = true;
	m_velocity = m_baseVelocity * p_speedIncrease;
	m_endOfSpeedPotionEffect = m_engineManager->getMasterClockSeconds() + p_duration;
}

/*
	Increase the damage by the p_damageIncrease (if 2, damage will be the double)
*/
void Player::increaseDamage(float p_duration, float p_damageIncrease)
{
	m_damagePotionEfect = true;
	m_damage = m_baseDamage * p_damageIncrease;
	m_endOfDamagePotionEffect = m_engineManager->getMasterClockSeconds() + p_duration;
}

/*
	Increase the armor by the p_armorIncrease (if 2, armor will be the double)
*/
void Player::increaseArmor(float p_duration, float p_armorIncrease)
{
	m_armorPotionEfect = true;
	m_armor = m_baseArmor * p_armorIncrease;
	m_endOfArmorPotionEffect = m_engineManager->getMasterClockSeconds() + p_duration;
}

/*
	Increase the attack speed by the p_attackSpeedIncrease (if 2, attackSpeed will be the double)
*/
void Player::increaseAtackSpeed(float p_duration, float p_atackSpeedIncrease)
{
	m_atackSpeedPotionEfect = true;
	m_atackSpeed = m_baseAtackSpeed * p_atackSpeedIncrease;
	m_endOfAtackSpeedPotionEffect = m_engineManager->getMasterClockSeconds() + p_duration;
}

void Player::move() {
	int t_sprint = 1;
	
	m_lastPosX = m_posX;
	m_lastPosY = m_posY;

	if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) || (!m_keyboard && sf::Joystick::isButtonPressed(0, (int)JoystickButton::LB))) {
		t_sprint = 2;
	}

	if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_X) >= 75)) {
		m_faceDirection = Direction::RIGHT;
		m_posX = m_lastPosX + (m_deltaTime * m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 2);
	}
	else if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_X) <= -75)) {
		m_faceDirection = Direction::LEFT;
		m_posX = m_lastPosX + (m_deltaTime * -m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 3);
	}
	
	if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_Y) >= 75)) {
		m_faceDirection = Direction::DOWN;
		m_posY = m_lastPosY + (m_deltaTime * m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
	}
	else if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_Y) <= -75)) {
		m_faceDirection = Direction::UP;
		m_posY = m_lastPosY + (m_deltaTime * -m_velocity * t_sprint);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
	}
	
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}

void Player::moveBackwards()
{
	m_posX = m_lastPosX;
	m_posY = m_lastPosY;

	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}

void Player::rangeAtack()
{
	if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::RIGHT_X) >= 75)) {
		m_faceDirection = Direction::RIGHT;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 2);
		launchProjectile();
	}
	else if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::RIGHT_X) <= -75)) {
		m_faceDirection = Direction::LEFT;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 3);
		launchProjectile();
	}
	else if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::RIGHT_Y) >= 75)) {
		m_faceDirection = Direction::DOWN;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
		launchProjectile();
	}
	else if ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::RIGHT_Y) <= -75)) {
		m_faceDirection = Direction::UP;
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 1);
		launchProjectile();
	}
	
	if (!m_hability1inCooldown && ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) || (!m_keyboard && sf::Joystick::isButtonPressed(0, (int)JoystickButton::RB)))) {
		hability1();
		if (m_hability1Launched) {
			m_hability1inCooldown = true;
			m_hability1ActivationTime = m_engineManager->getMasterClockSeconds();
		}
	}
	
	if (!m_hability2inCooldown && ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LT) >= 75))) {
		hability2();
		if (m_hability2Launched) {
			m_hability2inCooldown = true;
			m_hability2ActivationTime = m_engineManager->getMasterClockSeconds();
		}
	}
	
	if (!m_hability3inCooldown && ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::F)) || (!m_keyboard && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::RT) <= -75))) {
		hability3();
		if (m_hability3Launched) {
			m_hability3inCooldown = true;
			m_hability3ActivationTime = m_engineManager->getMasterClockSeconds();
		}
	}
}

void Player::updateHability1()
{
	float t_time = m_engineManager->getMasterClockSeconds();

	/* UPDATE MANA COOLDOWN */
	if (m_hability1inCooldown) {
		if (m_hability1Launched) {
			m_hability1->update(m_time, m_deltaTime);
			if (m_hability1->getReadyToDelete()) {
				delete m_hability1;
				m_hability1 = nullptr;
				m_hability1Launched = false;
			}
		}
		if (t_time > (m_hability1ActivationTime + m_hability1CooldownDuration))
			m_hability1inCooldown = false;
	}
}

void Player::updateHability2()
{
	float t_time = m_engineManager->getMasterClockSeconds();

	if (m_hability2inCooldown) {
		if (m_hability2Launched) {
			m_hability2->update(m_time, m_deltaTime);
			if (m_hability2->getReadyToDelete()) {
				delete m_hability2;
				m_hability2 = nullptr;
				m_hability2Launched = false;
			}
		}
		if (t_time > (m_hability2ActivationTime + m_hability2CooldownDuration))
			m_hability2inCooldown = false;
	}
}

void Player::updateHability3()
{
	float t_time = m_engineManager->getMasterClockSeconds();

	if (m_hability3inCooldown) {
		if (m_hability3Launched) {
			m_hability3->update(m_time, m_deltaTime);
			if (m_hability3->getReadyToDelete()) {
				delete m_hability3;
				m_hability3 = nullptr;
				m_hability3Launched = false;
			}
		}
		if (t_time > (m_hability3ActivationTime + m_hability3CooldownDuration))
			m_hability3inCooldown = false;
	}
}

void Player::updateManaConsumption()
{
	/* UPDATE MANA CONSUMPTION */
	if (m_mana >= m_hability1ManaConsumption)
		m_hability1EnoughMana = true;
	else
		m_hability1EnoughMana = false;

	if (m_mana >= m_hability2ManaConsumption)
		m_hability2EnoughMana = true;
	else
		m_hability2EnoughMana = false;

	if (m_mana >= m_hability3ManaConsumption)
		m_hability3EnoughMana = true;
	else
		m_hability3EnoughMana = false;
}

void Player::launchProjectile()
{
	if (!m_basicInCooldown && m_basicProjectiles.size() < m_maxProjectiles) {
		m_basicInCooldown = true;
		m_nextBasic = m_engineManager->getMasterClockSeconds() + m_atackSpeed;

		Projectile* t_projectile;
		if(!m_pasiveActive)
			t_projectile = new ProjectileStraight(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage, false, true);
		else {
			t_projectile = new ProjectileStraight(m_texturePath, m_bulletColor, m_faceDirection, m_posX, m_posY, m_damage, true, true);
			t_projectile->setLifeTime(0.75f);
		}
		t_projectile->setOwner(this);

		m_basicProjectiles.push_back(t_projectile);
		ScreenGame::m_projectileVector.push_back(t_projectile);
	}
}

void Player::pickPotion()
{
	for (int i = 0; i < ScreenGame::m_potionVector.size(); i++) {
		if (m_engineManager->checkCollision(this->m_spriteID, ScreenGame::m_potionVector[i]->getSpriteID())) {
			ScreenGame::m_potionVector[i]->setEffect(this);
		}
	}
}

void Player::updateHealthAndMana(double p_deltaTime)
{
	if (m_alive) {
		float t_health = m_maxHealth * (p_deltaTime / 100);
		increaseHealth(t_health);

		float t_mana = m_maxMana * (p_deltaTime / 100);
		increaseMana(t_mana);
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

	if (m_damagePotionEfect && t_currentTime >= m_endOfDamagePotionEffect) {
		m_damagePotionEfect = false;
		m_damage = m_baseDamage;
	}

	if (m_armorPotionEfect && t_currentTime >= m_endOfArmorPotionEffect) {
		m_armorPotionEfect = false;
		m_armor = m_baseArmor;
	}

	if (m_atackSpeedPotionEfect && t_currentTime >= m_endOfAtackSpeedPotionEffect) {
		m_atackSpeedPotionEfect = false;
		m_atackSpeed = m_baseAtackSpeed;
	}
}

void Player::update(double p_time, double p_deltaTime) {
	m_time		= p_time;
	m_deltaTime = p_deltaTime;

	m_nearEntityVector = m_hashGrid->getNearby(this);
	m_nearPotion = false;
	for (auto t_object : m_nearEntityVector) {
		switch (t_object->getEntity())
		{
		case Entities::TILE:
			if (m_engineManager->checkCollision(t_object->getSpriteID(), getSpriteID())) {
				Tile* t_tile = dynamic_cast<Tile*>(t_object);
				t_tile->applyEffect(this);
			}	
			break;
		case Entities::POTION:
			m_nearPotion = true;
			break;
		default:
			break;
		}
	}

	if (m_nearPotion && ((m_keyboard && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) || (!m_keyboard && sf::Joystick::isButtonPressed(0, (int)JoystickButton::X))))
		pickPotion();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		increaseHealth(200.f);
		increaseMana(200.f);
		receiveExperience(25.f);
	}

	move();

	updateHealthAndMana(p_deltaTime);

	rangeAtack();
	
	updatePotionEffects();
	updateBasicAtack();
	
	updateHability1();
	updateHability2();
	updateHability3();
	
	updateManaConsumption();
}

void Player::draw()
{
	if (m_hability1Launched)
		m_hability1->draw();

	if (m_hability2Launched)
		m_hability2->draw();

	if (m_hability3Launched)
		m_hability3->draw();

	for (int i = 0; i < m_basicProjectiles.size(); i++) {
		m_basicProjectiles[i]->draw();
	}

	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));

	/*
	sf::RectangleShape t_bounding;
	t_bounding.setSize({ getWidth(), getHeight() });
	t_bounding.setPosition(m_posX, m_posY);
	t_bounding.setOrigin(t_bounding.getGlobalBounds().width / 2, t_bounding.getGlobalBounds().height / 2);
	t_bounding.setFillColor(sf::Color(0, 0, 0, 0));
	t_bounding.setOutlineColor(sf::Color::Magenta);
	t_bounding.setOutlineThickness(2);

	m_engineManager->draw(t_bounding);
	*/
}
