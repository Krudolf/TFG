#include "pch.h"
#include "buttonText.h"
#include "engineManager.h"


ButtonText::ButtonText(std::string p_text, Point p_point) : Button(p_point)
{
	m_text		= p_text;
	m_textSize	= 50;

	m_buttonWidth	= 450.f;
	m_buttonHeight	= 80.f;

	m_button.setSize({ m_buttonWidth, m_buttonHeight });
	m_button.setFillColor(sf::Color(m_shoftBlue.r, m_shoftBlue.g, m_shoftBlue.b, m_shoftBlue.a));
	m_button.setOrigin({ m_buttonWidth / 2, m_buttonHeight / 2 });
	m_button.setPosition({ m_posX, m_posY });

	m_buttonText.setFont(*m_engineManager->getFont());
	m_buttonText.setCharacterSize(m_textSize);
	m_buttonText.setFillColor(sf::Color(m_darkGrey.r, m_darkGrey.g, m_darkGrey.b, m_darkGrey.a));
	m_buttonText.setString(m_text);
	m_buttonText.setPosition({ (m_posX - (m_buttonText.getLocalBounds().width / 2)), (m_posY - (m_buttonText.getLocalBounds().height / 2)) - 14 });
}


ButtonText::~ButtonText()
{
}

void ButtonText::draw()
{
	if (m_isFocused)
		m_buttonText.setFillColor(sf::Color(m_shoftBlue.r, m_shoftBlue.g, m_shoftBlue.b, m_shoftBlue.a));
	else
		m_buttonText.setFillColor(sf::Color(m_darkGrey.r, m_darkGrey.g, m_darkGrey.b, m_darkGrey.a));

	m_engineManager->draw(m_button);
	m_engineManager->draw(m_buttonText);
}
