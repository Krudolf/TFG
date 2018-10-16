#pragma once
#include "tinyxml2.h"

#include <SFML/Graphics.hpp>

class EngineManager;

class SceneMap
{
public:
	SceneMap(const char* p_urlXML, const char* p_urlTexture);
	~SceneMap();

	void draw();

private:
	EngineManager* m_engineManager;
	sf::Sprite**** m_mapMatriz4D;

	tinyxml2::XMLDocument*	m_mapDocument;
	tinyxml2::XMLElement*	m_rootElement;
	tinyxml2::XMLElement*	m_firstLayerElement;
	tinyxml2::XMLElement*	m_layerElement;
	tinyxml2::XMLElement*	m_tileElement;

	sf::Texture*	m_texture;

	int m_width;
	int m_height;
	int m_tileWidth;
	int m_tileHeight;
	int m_totalLayers;

};