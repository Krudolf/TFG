#include "pch.h"
#include "button.h"
#include "engineManager.h"


Button::Button(Point p_point)
{
	m_engineManager = &EngineManager::p();
	
	m_isFocused = false;
	m_isBlocked = false;

	m_posX = p_point.x;
	m_posY = p_point.y;
}

Button::~Button()
{
}

void Button::setIsFocused(bool p_isFocused)
{
	m_isFocused = p_isFocused;
	if (m_isFocused && m_isBlocked) {
		//m_button.setFillColor(sf::Color::Blue);
		m_button.setFillColor(sf::Color(0, 0, 255, 100));
	}
	else if (m_isFocused) {
		m_button.setFillColor(sf::Color::Blue);
	}
	else if (m_isBlocked) {
		m_button.setFillColor(sf::Color(169, 169, 169));
	}
	else
		m_button.setFillColor(sf::Color::Cyan);
}

void Button::setIsBlocked(bool p_isBlocked)
{
	m_isBlocked = p_isBlocked;
	if (m_isBlocked) {
		m_button.setFillColor(sf::Color(169,169,169));
	}
	else {
		m_button.setFillColor(sf::Color::Cyan);
	}
}
