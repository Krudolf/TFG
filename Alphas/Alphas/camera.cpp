#include "pch.h"
#include "camera.h"
#include <iostream>

Camera::Camera(sf::RenderWindow* p_window)
{
	//sf::View((target),(size of the rectangle));
	m_view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(600, 480));
	m_window = p_window;
	m_window->setView(*m_view);
}


Camera::~Camera()
{
	delete m_view;
}

void Camera::update()
{
	//std::cout << m_target->getPosition().x << ", " << m_target->getPosition().y << std::endl;
	m_view->setCenter(m_target->getPosition().x, m_target->getPosition().y);
	m_window->setView(*m_view);
}
