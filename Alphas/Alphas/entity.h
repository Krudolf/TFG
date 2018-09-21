#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(sf::RenderWindow* p_window);
	~Entity();

	virtual void update();
	void draw();

	sf::Vector2f getPosition() { return m_sprite->getPosition(); }

private:
	sf::RenderWindow* m_window;

protected:
	sf::Sprite*		m_sprite;
	sf::Texture*	m_texture;

};

