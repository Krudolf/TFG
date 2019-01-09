#include "pch.h"
#include "buttonImage.h"
#include "engineManager.h"

ButtonImage::ButtonImage(const char* p_path, Entities p_player, Point p_point) : Button(p_point)
{
	m_entityImage = p_player;

	m_buttonWidth	= 150.f;
	m_buttonHeight	= 150.f;

	m_button.setSize({ m_buttonWidth, m_buttonHeight });
	m_button.setFillColor(sf::Color(m_shoftBlue.r, m_shoftBlue.g, m_shoftBlue.b, m_shoftBlue.a));
	m_button.setOrigin({ m_buttonWidth / 2, m_buttonHeight / 2 });
	m_button.setPosition({ m_posX, m_posY });

	m_engineManager->loadTexture(p_path);
	
	int t_player = static_cast<int>(p_player);
	m_buttonImage.setTexture(*m_engineManager->getTexture(p_path));
	m_buttonImage.setTextureRect(sf::IntRect(0, 128 * t_player, 128, 128));
	//m_buttonImage.setOrigin(m_buttonImage.getTextureRect().width / 2, m_buttonImage.getTextureRect().height / 2);
	m_buttonImage.setScale(1, 1);
	m_buttonImage.setPosition({ (m_posX - (m_buttonImage.getLocalBounds().width / 2)), (m_posY - (m_buttonImage.getLocalBounds().height / 2))});
}


ButtonImage::~ButtonImage()
{
}

void ButtonImage::draw()
{
	m_engineManager->draw(m_button);
	m_engineManager->draw(m_buttonImage);
}
