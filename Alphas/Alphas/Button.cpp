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

	m_shoftGrey	= {159, 167, 170, 255};
	m_darkGrey	= {76, 99, 112, 255};
	m_shoftBlue = {73, 146, 230, 255};
	m_darkBlue	= {27, 55, 86, 255};
}

Button::~Button()
{
}

void Button::setIsFocused(bool p_isFocused)
{
	m_isFocused = p_isFocused;
	if (m_isFocused && m_isBlocked) {
		m_button.setFillColor(sf::Color(0, 0, 255, 100));
	}
	else if (m_isFocused) {
		m_button.setFillColor(sf::Color(m_darkGrey.r, m_darkGrey.g, m_darkGrey.b, m_darkGrey.a));
	}
	else if (m_isBlocked) {
		m_button.setFillColor(sf::Color(169, 169, 169));
	}
	else
		m_button.setFillColor(sf::Color(m_shoftBlue.r, m_shoftBlue.g, m_shoftBlue.b, m_shoftBlue.a));
}

void Button::setIsBlocked(bool p_isBlocked)
{
	m_isBlocked = p_isBlocked;
	if (m_isBlocked) {
		m_button.setFillColor(sf::Color(169,169,169));
	}
	else {
		m_button.setFillColor(sf::Color(m_shoftBlue.r, m_shoftBlue.g, m_shoftBlue.b, m_shoftBlue.a));
	}
}
