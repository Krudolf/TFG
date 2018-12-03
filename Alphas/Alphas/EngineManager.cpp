#include "pch.h"
#include "engineManager.h"

#include <iostream>


EngineManager::EngineManager()
{
	m_font = new sf::Font();
	if (!m_font->loadFromFile("assets/fonts/good_times_rg.ttf"))
		std::cout << "No se ha podido cargar la fuente Good Times" << std::endl;
	
	m_keyReleased = true;
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
	delete m_cameraView;
	delete m_window;
}

EngineManager& EngineManager::p()
{
	static EngineManager instance;
	return instance;
}

void EngineManager::createWindow(int p_resolutionX, int p_resolutionY, const char* p_name)
{
	m_window = new sf::RenderWindow(sf::VideoMode(p_resolutionX, p_resolutionY), p_name);
	m_width	= p_resolutionX;
	m_height = p_resolutionY;
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
	m_cameraView = new sf::View(sf::Vector2f(centerX, centerY), sf::Vector2f(width, height));
	m_cameraView->zoom(2);
}

void EngineManager::resetView()
{
	m_cameraView->reset(sf::FloatRect(0, 0, 1000, 1000));
	m_cameraView->zoom(0.5);
}

void EngineManager::loadTexture(const char * p_path)
{
	//Search the texture in the map, if not found we create the texture and add it to the map
	m_textureMapIterator = m_textureMap.find(p_path);
	
	//The texture was not found
	if (m_textureMapIterator == m_textureMap.end()) {
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

	/* DEBUG */
	//t_sprite->setOutlineColor(sf::Color::Red);
	//t_sprite->setOutlineThickness(2);

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
	//t_sprite->setOrigin(t_sprite->getTextureRect().width / 2, t_sprite->getTextureRect().height / 2);
	t_sprite->setScale(p_scale, p_scale);
	t_sprite->setPosition(p_posX, p_posY);

	/* DEBUG */
	//t_sprite->setOutlineColor(sf::Color::Red);
	//t_sprite->setOutlineThickness(2);

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

bool EngineManager::checkCollision(int p_spriteID1, int p_spriteID2)
{
	sf::Sprite* t_sprite1 = m_spriteVector[p_spriteID1];
	sf::Sprite* t_sprite2 = m_spriteVector[p_spriteID2];

	bool t_collide = t_sprite1->getGlobalBounds().intersects(t_sprite2->getGlobalBounds());

	return t_collide;
}
