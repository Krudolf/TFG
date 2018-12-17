#include "pch.h"
#include "fillBar.h"
#include "engineManager.h"


FillBar::FillBar(float p_sizeX, float p_sizeY, float p_posX, float p_posY, Color p_color1, Color p_color2)
{
	m_engineManager = &EngineManager::p();
	m_offset = 4.f;
	m_sizeX = p_sizeX;

	m_background.setSize({ p_sizeX, p_sizeY });
	m_background.setPosition(p_posX, p_posY);
	m_background.setOrigin(m_background.getGlobalBounds().width / 2, m_background.getGlobalBounds().height / 2);
	m_background.setFillColor(sf::Color(p_color1.r, p_color1.g, p_color1.b, p_color1.a));

	m_upperground.setSize({ p_sizeX - m_offset, p_sizeY - m_offset });
	m_upperground.setPosition(p_posX - p_sizeX / 2 + m_offset / 2, p_posY);
	m_upperground.setOrigin(0, m_upperground.getGlobalBounds().height / 2);
	m_upperground.setFillColor(sf::Color(p_color2.r, p_color2.g, p_color2.b, p_color2.a));
}


FillBar::~FillBar()
{
}

void FillBar::update(float p_size)
{
	m_upperground.setScale(p_size, 1);
}

void FillBar::update(float p_size, float p_posX, float p_posY)
{
	float t_offsetX = 3.f;
	float t_offsetY = 40.f;
	m_background.setPosition(p_posX - t_offsetX, p_posY - t_offsetY);
	m_upperground.setPosition((p_posX - m_sizeX / 2 + m_offset / 2) - t_offsetX, p_posY - t_offsetY);
	m_upperground.setScale(p_size, 1);
}

void FillBar::draw()
{
	m_engineManager->draw(m_background);
	m_engineManager->draw(m_upperground);
}
