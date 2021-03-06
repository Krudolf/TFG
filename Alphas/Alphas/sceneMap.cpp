#include "pch.h"
#include "sceneMap.h"
#include "engineManager.h"
#include "screenGame.h"
#include "tile.h"
#include "tileBlock.h"
#include "tileSkewer.h"


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

	m_engineManager->loadTexture(p_urlTexture);
	m_engineManager->getTexture(p_urlTexture)->getSize().x;

	int	t_rows		= m_engineManager->getTexture(p_urlTexture)->getSize().x / m_tileWidth;
	int	t_columns	= m_engineManager->getTexture(p_urlTexture)->getSize().y / m_tileHeight;

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
				
				gid--;
				int t_textureLeft	= (gid % t_rows * m_tileWidth);
				int t_textureTop	= (gid / t_columns * m_tileWidth);

				Tile* t_tile;
				if (gid < 40) {
					if (gid == 20) {
						t_tile = new TileSkewer(p_urlTexture, t_textureLeft, t_textureTop, m_tileWidth, m_tileHeight, posX, posY, gid);
						ScreenGame::m_tileCollisionVector.push_back(t_tile);
					}
					else {
						t_tile = new Tile(p_urlTexture, t_textureLeft, t_textureTop, m_tileWidth, m_tileHeight, posX, posY, gid);
					}
				}
				else{
					t_tile = new TileBlock(p_urlTexture, t_textureLeft, t_textureTop, m_tileWidth, m_tileHeight, posX, posY, gid);
					ScreenGame::m_tileCollisionVector.push_back(t_tile);
				}

				m_mapMatrix4D[l][h][w] = t_tile;
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
}

void SceneMap::draw()
{
	int viewCenterX = m_engineManager->getCameraView()->getCenter().x;
	int viewCenterY = m_engineManager->getCameraView()->getCenter().y;
	int viewSizeX = m_engineManager->getCameraView()->getSize().x;
	int viewSizeY = m_engineManager->getCameraView()->getSize().y;

	int startX	= (viewCenterX - viewSizeX / 2) / m_tileWidth;
	int endX	= (viewCenterX + viewSizeX / 2) / m_tileWidth + 1;
	int startY	= (viewCenterY - viewSizeY / 2) / m_tileHeight;
	int endY	= (viewCenterY + viewSizeY / 2) / m_tileHeight + 1;

	if (startX < 0)
		startX = 0;
	
	if (startY < 0)
		startY = 0;

	if (endX > m_width)
		endX = m_width;

	if (endY > m_height)
		endY = m_height;
	
	for (int l = 0; l < m_totalLayers; l++) {
		for (int h = startY; h < endY; h++) {
			for (int w = startX; w < endX; w++) {
				m_mapMatrix4D[l][h][w]->draw();
			}
		}
	}
}
