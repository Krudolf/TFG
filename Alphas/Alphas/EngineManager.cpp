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

	for (int i = 0; i < m_textureVector.size(); i++) {
		delete m_textureVector[i];
		m_textureVector[i] = nullptr;
	}
	m_textureVector.clear();

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

void EngineManager::createCameraView(int centerX, int centerY, int width, int height)
{
	m_cameraView = new sf::View(sf::Vector2f(centerX, centerY), sf::Vector2f(width, height));
}

int EngineManager::loadTexture(const char * p_path)
{
	int textureID = -1;

	//Search if the texture is already loaded
	bool isLoaded = false;
	for (int i = 0; i < m_textureNameVector.size(); i++) {
		//If is  loaded we return the ID
		if ((std::strcmp(m_textureNameVector[i], p_path) == 0)) {
			isLoaded = true;
			textureID = i;
			break;
		}
	}

	//If not is loaded we create that texture and return its ID
	if (!isLoaded) {
		sf::Texture* t_texture = new sf::Texture();
		if (!t_texture->loadFromFile(p_path))
		{
			std::cout << "No se ha podido cargar la textura " << p_path << std::endl;
			return textureID;
		}
	
		m_textureNameVector.push_back(p_path);
		m_textureVector.push_back(t_texture);
		textureID = m_textureVector.size()-1;
	}

	return textureID;
}

int EngineManager::createSprite(int p_textureID, float p_scale, bool p_centerOrigin)
{
	int spriteID = -1;

	sf::Sprite* t_sprite = new sf::Sprite();
	t_sprite->setTexture(*m_textureVector[p_textureID]);
	t_sprite->setTextureRect(sf::IntRect(0, 0, 128, 128));
	t_sprite->setOrigin(t_sprite->getTextureRect().width / 2, t_sprite->getTextureRect().height / 2);
	t_sprite->setScale(p_scale, p_scale);

	m_spriteVector.push_back(t_sprite);
	spriteID = m_spriteVector.size() - 1;

	return spriteID;
}

void EngineManager::setSpriteFrame(int p_spriteID, int p_entity, int p_frame)
{
	this->getSprite(p_spriteID)->setTextureRect(sf::IntRect(128 * p_frame, 128 * p_entity, 128, 128));
}

void EngineManager::createMap()
{
	mapTexture = new sf::Texture;
	if (!mapTexture->loadFromFile("assets/mapa.png"))
	{
		std::cout << "No se ha podido cargar la textura del map" << std::endl;
	}

	mapSprite = new sf::Sprite();
	mapSprite->setTexture(*mapTexture);
	mapSprite->setOrigin(mapSprite->getTextureRect().width / 2, mapSprite->getTextureRect().height / 2);
	mapSprite->setScale(2.0, 2.0);
}

