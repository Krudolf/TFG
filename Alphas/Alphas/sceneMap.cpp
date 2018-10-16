#include "pch.h"
#include "sceneMap.h"
#include "engineManager.h"

#include <iostream>

SceneMap::SceneMap(const char* p_urlXML, const char* p_urlTexture)
{
	m_engineManager = &EngineManager::p();
	
	m_mapDocument = new tinyxml2::XMLDocument();
	m_mapDocument->LoadFile(p_urlXML);

	//Get the root (map)
	m_rootElement	= m_mapDocument->RootElement();
	
	//Get some useful attributes from the map
	m_rootElement->QueryIntAttribute("width", &m_width);
	m_rootElement->QueryIntAttribute("height", &m_height);
	m_rootElement->QueryIntAttribute("tilewidth", &m_tileWidth);
	m_rootElement->QueryIntAttribute("tileheight", &m_tileHeight);
	m_totalLayers = 0;
	
	float centerX = (m_width * m_tileWidth)/2;
	float centerY = (m_height * m_tileHeight)/2;

	//Get the first layer
	m_firstLayerElement = m_rootElement->FirstChildElement("layer");
	m_layerElement = m_firstLayerElement;
	while (m_layerElement != NULL) {
		m_layerElement = m_layerElement->NextSiblingElement();
		m_totalLayers++;
	}
	
	//Get the first tile
	m_tileElement	= m_firstLayerElement->FirstChildElement()->FirstChildElement();

	//m_engineManager->loadTexture(p_urlTexture);
	m_texture = new sf::Texture();
	if (!m_texture->loadFromFile(p_urlTexture))
	{
		std::cout << "No se ha podido cargar la textura " << p_urlTexture << std::endl;
	}

	/*	matriz 4D [layer][width][height] -> sf::Sprite****	*/
	int gid = 0;
	float posX, posY;
	m_mapMatriz4D = new sf::Sprite***[m_totalLayers];
	for (int l = 0; l < m_totalLayers; l++) {
		m_mapMatriz4D[l] = new sf::Sprite**[m_height];
		for (int h = 0; h < m_height; h++) {
			m_mapMatriz4D[l][h] = new sf::Sprite*[m_width];
			for (int w = 0; w < m_width; w++) {
				m_tileElement->QueryIntAttribute("gid", &gid);
				m_tileElement = m_tileElement->NextSiblingElement();

				posX = centerX - (w * m_tileWidth);
				posY = centerY - (h * m_tileHeight);

				sf::Sprite* t_tileSprite = new sf::Sprite();
				t_tileSprite->setTexture(*m_texture);
				t_tileSprite->setTextureRect(sf::IntRect(((gid-1) % 4 * m_tileWidth), ((gid-1) / 4 * m_tileWidth), m_tileWidth, m_tileHeight));
				t_tileSprite->setPosition(posX, posY);
				t_tileSprite->setOrigin(t_tileSprite->getTextureRect().width / 2, t_tileSprite->getTextureRect().height / 2);

				m_mapMatriz4D[l][h][w] = t_tileSprite;
			}
		}
	}
}


SceneMap::~SceneMap()
{
	for (int l = 0; l < m_totalLayers; l++) {
		for (int h = 0; h < m_height; h++) {
			for (int w = 0; w < m_width; w++) {
				delete m_mapMatriz4D[l][h][w];
			}
			delete m_mapMatriz4D[l][h];
		}
		delete m_mapMatriz4D[l];
	}
	delete m_mapMatriz4D;

	delete m_mapDocument;
	//delete m_rootElement;
	//delete m_layerElement;
	//delete m_tileElement;

	delete m_texture;
}

void SceneMap::draw()
{
	for (int l = 0; l < m_totalLayers; l++) {
		for (int h = 0; h < m_height; h++) {
			for (int w = 0; w < m_width; w++) {
				m_engineManager->draw(m_mapMatriz4D[l][h][w]);
			}
		}
	}
}

