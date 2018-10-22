#include "pch.h"
#include "engineManager.h"
#include "quadTree.h"
#include <iostream>


EngineManager::EngineManager()
{
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
	m_cameraView->zoom(2);
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

void EngineManager::loadMap(const char * p_urlXML, const char * p_urlTexture)
{
	m_mapDocument = new tinyxml2::XMLDocument();
	m_mapDocument->LoadFile(p_urlXML);

	//Get the root (map)
	m_rootElement = m_mapDocument->RootElement();

	//Get some useful attributes from the map
	m_rootElement->QueryIntAttribute("width", &m_width);
	m_rootElement->QueryIntAttribute("height", &m_height);
	m_rootElement->QueryIntAttribute("tilewidth", &m_tileWidth);
	m_rootElement->QueryIntAttribute("tileheight", &m_tileHeight);
	m_totalLayers = 0;

	//float centerX = (m_width * m_tileWidth)/2;
	//float centerY = (m_height * m_tileHeight)/2;

	//Get the first layer
	m_firstLayerElement = m_rootElement->FirstChildElement("layer");
	m_layerElement = m_firstLayerElement;
	while (m_layerElement != NULL) {
		m_layerElement = m_layerElement->NextSiblingElement();
		m_totalLayers++;
	}

	//Get the first tile
	m_tileElement = m_firstLayerElement->FirstChildElement()->FirstChildElement();

	/*	matriz 4D [layer][width][height] -> sf::Sprite****	*/
	int gid = 0;
	float posX, posY;
	m_mapMatrix4D = new sf::Sprite***[m_totalLayers];
	for (int l = 0; l < m_totalLayers; l++) {
		m_mapMatrix4D[l] = new sf::Sprite**[m_height];
		for (int h = 0; h < m_height; h++) {
			m_mapMatrix4D[l][h] = new sf::Sprite*[m_width];
			for (int w = 0; w < m_width; w++) {
				m_tileElement->QueryIntAttribute("gid", &gid);
				m_tileElement = m_tileElement->NextSiblingElement();

				posX = (w * m_tileWidth);
				posY = (h * m_tileHeight);

				//posX = centerX - (w * m_tileWidth);
				//posY = centerY - (h * m_tileHeight);

				sf::Sprite* t_tileSprite = new sf::Sprite();
				t_tileSprite->setTexture(*m_textureMap[p_urlTexture]);
				t_tileSprite->setTextureRect(sf::IntRect(((gid - 1) % 4 * m_tileWidth), ((gid - 1) / 4 * m_tileWidth), m_tileWidth, m_tileHeight));
				t_tileSprite->setPosition(posX, posY);
				t_tileSprite->setOrigin(t_tileSprite->getTextureRect().width / 2, t_tileSprite->getTextureRect().height / 2);

				m_mapMatrix4D[l][h][w] = t_tileSprite;
			}
		}
	}
}

void EngineManager::deleteMap()
{
	for (int l = 0; l < m_totalLayers; l++) {
		for (int h = 0; h < m_height; h++) {
			for (int w = 0; w < m_width; w++) {
				delete m_mapMatrix4D[l][h][w];
			}
			delete m_mapMatrix4D[l][h];
		}
		delete m_mapMatrix4D[l];
	}
	delete m_mapMatrix4D;

	delete m_mapDocument;
	//delete m_rootElement;
	//delete m_layerElement;
	//delete m_tileElement;
}

void EngineManager::drawMap()
{
	for (int l = 0; l < m_totalLayers; l++) {
		for (int h = 0; h < m_height; h++) {
			for (int w = 0; w < m_width; w++) {
				draw(m_mapMatrix4D[l][h][w]);
			}
		}
	}
}

void EngineManager::fillQuadTree(QuadTree * p_quadTree)
{
	for (int l = 0; l < m_totalLayers; l++) {
		for (int h = 0; h < m_height; h++) {
			for (int w = 0; w < m_width; w++) {
				p_quadTree->insert(m_mapMatrix4D[l][h][w]);
			}
		}
	}
}

bool EngineManager::checkCollision(int p_spriteID1, int p_spriteID2)
{
	sf::Sprite* t_sprite1 = m_spriteVector[p_spriteID1];
	sf::Sprite* t_sprite2 = m_spriteVector[p_spriteID2];

	bool t_collide = t_sprite1->getGlobalBounds().intersects(t_sprite2->getGlobalBounds());

	return t_collide;
}
