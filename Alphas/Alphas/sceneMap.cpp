#include "pch.h"
#include "sceneMap.h"
#include "engineManager.h"


SceneMap::SceneMap(const char* p_urlXML, const char* p_urlTexture)
{	
	m_engineManager = &EngineManager::p();

	m_engineManager->loadTexture(p_urlTexture);
	m_engineManager->loadMap(p_urlXML, p_urlTexture);
}


SceneMap::~SceneMap()
{
	m_engineManager->deleteMap();
}

void SceneMap::draw()
{
	m_engineManager->drawMap();
}

int SceneMap::getWidth() 
{ 
	return m_engineManager->getMapWidth();
}

int SceneMap::getHeight()
{ 
	return m_engineManager->getMapHeight();
}

