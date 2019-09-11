#include "pch.h"
#include "text.h"
#include "engineManager.h"
#include "color.h"

Text::Text(const char* p_text)
{
	Color m_darkGrey = { 76, 99, 112, 255 };

	m_engineManager = &EngineManager::p();

	m_text.setFont(*m_engineManager->getFont());
	m_text.setCharacterSize(15);
	m_text.setFillColor(sf::Color(m_darkGrey.r, m_darkGrey.g, m_darkGrey.b, m_darkGrey.a));
	m_text.setString(p_text);
}


Text::~Text()
{
}


void Text::centerOrigin()
{
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
}

void Text::draw()
{
	m_engineManager->draw(m_text);
}
