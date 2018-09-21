#include "pch.h"
#include "player.h"

#include <iostream>

Player::Player(sf::RenderWindow* p_window) : Entity(p_window)
{
	m_texture = new sf::Texture;
	if (!m_texture->loadFromFile("assets/azul.png"))
	{
		std::cout << "No se ha podido cargar la textura del personaje" << std::endl;
	}

	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*m_texture);
}


Player::~Player()
{
	delete m_sprite;

	delete m_texture;
}

void Player::move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_sprite->move(sf::Vector2f(1, 0));
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_sprite->move(sf::Vector2f(-1, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_sprite->move(sf::Vector2f(0, 1));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_sprite->move(sf::Vector2f(0, -1));
	}
}

void Player::update() {
	move();
}