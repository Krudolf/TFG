#pragma once

class EngineManager;

class SceneMap
{
public:
	SceneMap(const char* p_urlXML, const char* p_urlTexture);
	~SceneMap();

	void draw();
	
	int getWidth();
	int getHeight();

private:
	EngineManager* m_engineManager;



};