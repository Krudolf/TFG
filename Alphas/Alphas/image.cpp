#include "pch.h"
#include "image.h"
#include "engineManager.h"


Image::Image(const char * p_path, Point p_point) {
	m_engineManager = &EngineManager::p();

	m_engineManager->loadTexture(p_path);

	m_width		= m_engineManager->getTexture(p_path)->getSize().x;
	m_height	= m_engineManager->getTexture(p_path)->getSize().y;

	m_image.setTexture(*m_engineManager->getTexture(p_path));
	m_image.setTextureRect(sf::IntRect(0, 0, m_width , m_height));
	m_image.setPosition(p_point.x, p_point.y);
	m_image.setOrigin(m_image.getTextureRect().width / 2, m_image.getTextureRect().height / 2);
}

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

Image::Image(const char * p_path, int p_row, Point p_point)
{
	m_engineManager = &EngineManager::p();

	m_engineManager->loadTexture(p_path);

	m_image.setTexture(*m_engineManager->getTexture(p_path));
	m_image.setTextureRect(sf::IntRect(0, 335 * p_row, 512, 335));
	m_image.setPosition(p_point.x, p_point.y);
	//m_image.setScale(1.2, 1.2);
	m_image.setOrigin(m_image.getTextureRect().width / 2, m_image.getTextureRect().height / 2);
}

Image::Image(Stats p_stats, float p_posX, float p_posY)
{
	m_engineManager = &EngineManager::p();

	const char* t_path = "assets/habilitySheet.png";
	m_engineManager->loadTexture(t_path);

	int t_player = static_cast<int>(p_stats);
	m_image.setTexture(*m_engineManager->getTexture(t_path));
	m_image.setTextureRect(sf::IntRect(32 * t_player, 32 * 3, 32, 32));
	m_image.setPosition(p_posX, p_posY);
	m_image.setOrigin(m_image.getTextureRect().width / 2, m_image.getTextureRect().height / 2);
}

Image::~Image()
{
}

void Image::changeFrame(int p_frame)
{
	m_image.setTextureRect(sf::IntRect(0, 128 * p_frame, 128, 128));
}

void Image::changeFrameHability(int p_frame)
{
	m_image.setTextureRect(sf::IntRect(0, 335 * p_frame, 512, 335));
}

void Image::draw()
{
	m_engineManager->draw(m_image);
}
