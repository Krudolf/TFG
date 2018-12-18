#include "pch.h"
#include "engineManager.h"

#include <iostream>


EngineManager::EngineManager()
{
	m_gameView = new sf::View();

	m_font = new sf::Font();
	if (!m_font->loadFromFile("assets/fonts/good_times_rg.ttf"))
		std::cout << "No se ha podido cargar la fuente Good Times" << std::endl;
	
	m_keyReleased	= true;

	m_masterTime	= sf::Time::Zero;
	m_pauseTime		= sf::Time::Zero;
}


EngineManager::~EngineManager()
{
	for (int i = 0; i < m_spriteVector.size(); i++) {
		delete m_spriteVector[i];
		m_spriteVector[i] = nullptr;
	}
	m_spriteVector.clear();

	for (std::map<const char*, sf::Texture*>::iterator it = m_textureMap.begin(); it != m_textureMap.end(); ++it) {
		delete it->second;
		it->second = nullptr;
	}
	m_textureMap.clear();

	delete m_font;
	delete m_gameView;
	delete m_window;
}

EngineManager& EngineManager::p()
{
	static EngineManager instance;
	return instance;
}

void EngineManager::createWindow(int p_resolutionX, int p_resolutionY, const char* p_name)
{
	m_width	= p_resolutionX;
	m_height = p_resolutionY;

	m_window = new sf::RenderWindow(sf::VideoMode(p_resolutionX, p_resolutionY), p_name);
	m_interfaceView = m_window->getDefaultView();
}

void EngineManager::closeWindow()
{
	m_window->close();
}

void EngineManager::draw(sf::Sprite* p_sprite)
{
	m_window->draw(*p_sprite);
}

void EngineManager::draw(sf::RectangleShape p_rectangle)
{
	m_window->draw(p_rectangle);
}

void EngineManager::draw(sf::Text p_text)
{
	m_window->draw(p_text);
}

void EngineManager::draw(sf::Sprite p_sprite)
{
	m_window->draw(p_sprite);
}

void EngineManager::drawCircle()
{
	m_window->draw(m_circle);
}

void EngineManager::checkEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();

		if (event.type == sf::Event::KeyReleased) {
			m_keyReleased = true;
		}
	}
}

void EngineManager::createCameraView(int centerX, int centerY, int width, int height)
{
	m_gameView->setCenter(sf::Vector2f(centerX, centerY));
	m_gameView->setSize(sf::Vector2f(width, height));
}

void EngineManager::setTargetGameView(float p_posX, float p_posY)
{
	m_gameView->setCenter(p_posX, p_posY);
}

void EngineManager::useGameView()
{
	m_window->setView(*m_gameView);
}

void EngineManager::useInterfaceView()
{
	m_window->setView(m_interfaceView);
}

float EngineManager::updateMasterClock()
{
	m_masterTime += m_masterClock.getElapsedTime();
	m_masterClock.restart();

	return m_masterTime.asSeconds();
}

float EngineManager::getMasterClockSeconds()
{
	return m_masterTime.asSeconds();
}

void EngineManager::pauseClock()
{
	m_pauseTime = m_masterTime;
}

void EngineManager::resumeClock()
{
	m_masterTime = m_pauseTime;
}

void EngineManager::restartClock()
{
	m_masterClock.restart();
}

void EngineManager::loadTexture(const char * p_path)
{
	//Search the texture in the map, if not found we create the texture and add it to the map
	m_textureMapIterator = m_textureMap.find(p_path);
	
	//The texture was not found --> Create the texture
	if (m_textureMapIterator == m_textureMap.end()) {
		std::cout << "CREAMOS LA TEXTURA " << p_path << std::endl;
		sf::Texture* t_texture = new sf::Texture();
		if (!t_texture->loadFromFile(p_path))
		{
			std::cout << "No se ha podido cargar la textura " << p_path << std::endl;
		}
	
		m_textureMap.insert(std::pair<const char*, sf::Texture*>(p_path, t_texture));
	}
}

int EngineManager::createSprite(const char* p_texturePath, float p_scale, bool p_centerOrigin)
{
	int spriteID = -1;

	sf::Sprite* t_sprite = new sf::Sprite();
	t_sprite->setTexture(*m_textureMap[p_texturePath]);
	t_sprite->setTextureRect(sf::IntRect(0, 0, 128, 128));
	t_sprite->setOrigin(t_sprite->getTextureRect().width / 2.f, t_sprite->getTextureRect().height / 2.f);
	t_sprite->setScale(p_scale, p_scale);

	m_spriteVector.push_back(t_sprite);
	spriteID = m_spriteVector.size() - 1;

	return spriteID;
}

int EngineManager::createSprite(const char * p_texturePath, float p_scale, bool p_centerOrigin, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY)
{
	int spriteID = -1;

	sf::Sprite* t_sprite = new sf::Sprite();
	t_sprite->setTexture(*m_textureMap[p_texturePath]);
	t_sprite->setTextureRect(sf::IntRect(p_textureLeft, p_textureTop, p_textureWidth, p_textureHeight));
	if(p_centerOrigin)
		t_sprite->setOrigin(t_sprite->getTextureRect().width / 2, t_sprite->getTextureRect().height / 2);
	t_sprite->setScale(p_scale, p_scale);
	t_sprite->setPosition(p_posX, p_posY);

	m_spriteVector.push_back(t_sprite);
	spriteID = m_spriteVector.size() - 1;

	return spriteID;
}

void EngineManager::setSpriteFrame(int p_spriteID, int p_entity, int p_frame)
{
	this->getSprite(p_spriteID)->setTextureRect(sf::IntRect(128 * p_frame, 128 * p_entity, 128, 128));
}

void EngineManager::getDirection(double p_posEntity1X, double p_posEntity1Y, double p_posEntity2X, double p_posEntity2Y, float & p_directionX, float & p_directionY)
{
	sf::Vector2f t_entity1(p_posEntity1X, p_posEntity1Y);
	sf::Vector2f t_entity2(p_posEntity2X, p_posEntity2Y);
	
	sf::Vector2f t_direction(t_entity1 - t_entity2);

	float t_length = sqrt((t_direction.x * t_direction.x) + (t_direction.y * t_direction.y));
	if (t_length != 0) {
		p_directionX = t_direction.x / t_length;
		p_directionY = t_direction.y / t_length;
	}
	else {
		p_directionX = t_direction.x;
		p_directionY = t_direction.y;
	}
		

}

void EngineManager::createCircle(float p_posX, float p_posY, float p_radius)
{
	m_circle.setPosition(p_posX, p_posY);
	m_circle.setRadius(p_radius);
	m_circle.setFillColor(sf::Color(90, 250, 60, 50));
	m_circle.setOrigin(m_circle.getGlobalBounds().width / 2, m_circle.getGlobalBounds().height / 2);
}

/*
	p_spriteID1			-> Entity (player or enemy) where we check if one bullet collides with
	p_bulletSpriteID2	-> Bullet which we are going to check if collides
*/
bool EngineManager::checkCollision(int p_spriteID1, int p_bulletSpriteID2)
{
	sf::Sprite* t_entity = m_spriteVector[p_spriteID1];
	sf::Sprite* t_bullet = m_spriteVector[p_bulletSpriteID2];

	bool t_collide = t_entity->getGlobalBounds().contains(t_bullet->getPosition());

	return t_collide;
}

bool EngineManager::checkCollisionCircle(int p_spriteID)
{
	sf::Sprite* t_entity = m_spriteVector[p_spriteID];

	bool t_collide = m_circle.getGlobalBounds().contains(t_entity->getPosition());

	return t_collide;
}
