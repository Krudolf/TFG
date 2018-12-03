#include "pch.h"
#include "sceneMap.h"
#include "engineManager.h"
#include "screenGame.h"
#include "tile.h"


SceneMap::SceneMap(const char* p_urlXML, const char* p_urlTexture)
{	
	m_engineManager = &EngineManager::p();

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
	m_mapMatrix4D = new Tile***[m_totalLayers];
	for (int l = 0; l < m_totalLayers; l++) {
		m_mapMatrix4D[l] = new Tile**[m_height];
		for (int h = 0; h < m_height; h++) {
			m_mapMatrix4D[l][h] = new Tile*[m_width];
			for (int w = 0; w < m_width; w++) {
				m_tileElement->QueryIntAttribute("gid", &gid);
				m_tileElement = m_tileElement->NextSiblingElement();

				float posX = (w * m_tileWidth);
				float posY = (h * m_tileHeight);

				int t_textureLeft	= ((gid - 1) % 4 * m_tileWidth);
				int t_textureTop	= ((gid - 1) / 4 * m_tileWidth);

				Tile* t_tile = new Tile(p_urlTexture, t_textureLeft, t_textureTop, m_tileWidth, m_tileHeight, posX, posY, gid);

				m_mapMatrix4D[l][h][w] = t_tile;
				ScreenGame::m_entityVector.push_back(t_tile);
			}
		}
	}
}


SceneMap::~SceneMap()
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

void SceneMap::draw()
{
	for (int l = 0; l < m_totalLayers; l++) {
		for (int h = 0; h < m_height; h++) {
			for (int w = 0; w < m_width; w++) {
				m_mapMatrix4D[l][h][w]->draw();
			}
		}
	}
}
