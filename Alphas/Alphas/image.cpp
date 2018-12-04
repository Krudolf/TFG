#include "pch.h"
#include "image.h"
#include "engineManager.h"

Image::Image(const char * p_path, Entities p_player, Point p_point)
{
	m_engineManager = &EngineManager::p();

	m_engineManager->loadTexture(p_path);

	int t_player = static_cast<int>(p_player);
	m_image.setTexture(*m_engineManager->getTexture(p_path));
	m_image.setTextureRect(sf::IntRect(0, 128 * t_player, 128, 128));
	m_image.setScale(2,2);
	m_image.setPosition(p_point.x, p_point.y);
	m_image.setOrigin(m_image.getTextureRect().width / 2, m_image.getTextureRect().height / 2);
}

Image::~Image()
{
}

void Image::changeFrame(int p_frame)
{
	m_image.setTextureRect(sf::IntRect(0, 128 * p_frame, 128, 128));
}

void Image::draw()
{
	m_engineManager->draw(m_image);
}
