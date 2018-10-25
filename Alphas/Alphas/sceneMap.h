#pragma once

#include "tinyxml2.h"

class EngineManager;
class Tile;

class SceneMap
{
public:
	SceneMap(const char* p_urlXML, const char* p_urlTexture);
	~SceneMap();

	void draw();
	
	int getWidth() { return (m_width*m_tileWidth); };
	int getHeight() { return (m_height*m_tileHeight); };

private:
	EngineManager* m_engineManager;

	Tile**** m_mapMatrix4D;

	tinyxml2::XMLDocument*	m_mapDocument;
	tinyxml2::XMLElement*	m_rootElement;
	tinyxml2::XMLElement*	m_firstLayerElement;
	tinyxml2::XMLElement*	m_layerElement;
	tinyxml2::XMLElement*	m_tileElement;

	int m_width;
	int m_height;
	int m_tileWidth;
	int m_tileHeight;
	int m_totalLayers;

};