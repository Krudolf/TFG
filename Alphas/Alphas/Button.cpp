#include "pch.h"
#include "button.h"
#include "engineManager.h"


Button::Button(std::string p_text, Point p_point)
{
	m_engineManager = &EngineManager::p();
	
	m_isFocused = false;

	m_text = p_text;
	m_textSize = 50;

	m_buttonWidth = 450.f;
	m_buttonHeight = 80.f;

	m_button.setSize({ m_buttonWidth, m_buttonHeight });
	m_button.setFillColor(sf::Color::Cyan);
	m_button.setOutlineColor(sf::Color::Black);
	m_button.setOutlineThickness(5);
	m_button.setOrigin({ m_buttonWidth / 2, m_buttonHeight / 2 });
	m_button.setPosition({ p_point.x, p_point.y });

	m_buttonText.setFont(*m_engineManager->getFont());
	m_buttonText.setCharacterSize(m_textSize);
	m_buttonText.setFillColor(sf::Color::Black);
	m_buttonText.setString(m_text);
	m_buttonText.setPosition({(p_point.x - (m_buttonText.getLocalBounds().width/2)), (p_point.y - (m_buttonText.getLocalBounds().height / 2)) - 14 });
}

Button::~Button()
{
}

void Button::setIsFocused(bool p_isFocused)
{
	m_isFocused = p_isFocused;
	if (m_isFocused) {
		m_button.setFillColor(sf::Color::Blue);
	}
	else {
		m_button.setFillColor(sf::Color::Cyan);
	}
}

void Button::draw()
{
	m_engineManager->draw(m_button);
	m_engineManager->draw(m_buttonText);
}
