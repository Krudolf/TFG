#include "pch.h"
#include "engineManager.h"
#include <iostream>


EngineManager::EngineManager()
{
}


EngineManager::~EngineManager()
{
	delete mapSprite;
	delete mapTexture;

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
}

void EngineManager::draw(sf::Sprite* p_sprite)
{
	m_window->draw(*p_sprite);
}

void EngineManager::createCameraView(int centerX, int centerY, int width, int height)
{
	m_cameraView = new sf::View(sf::Vector2f(centerX, centerY), sf::Vector2f(width, height));
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
	t_sprite->setOrigin(t_sprite->getTextureRect().width / 2, t_sprite->getTextureRect().height / 2);
	t_sprite->setScale(p_scale, p_scale);

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

bool EngineManager::checkCollision(int p_spriteID1, int p_spriteID2)
{
	sf::Sprite* t_sprite1 = m_spriteVector[p_spriteID1];
	sf::Sprite* t_sprite2 = m_spriteVector[p_spriteID2];

	bool t_collide = t_sprite1->getGlobalBounds().intersects(t_sprite2->getGlobalBounds());

	return t_collide;
}
