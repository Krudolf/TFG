
#include "pch.h"
#include "entity.h"
#include <iostream>

Entity::Entity(sf::RenderWindow* p_window)
{
	m_window = p_window;
}


Entity::~Entity()
{
	delete m_sprite;
}

void Entity::update()
{

}

void Entity::draw()
{
	m_window->draw(*m_sprite);
}
