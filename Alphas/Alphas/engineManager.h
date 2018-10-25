#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class EngineManager
{
public:
	~EngineManager();
	static EngineManager& p();

	/* WINDOW */
	void createWindow(int p_resolutionX, int p_resolutionY, const char* p_name);
	sf::RenderWindow* getWindow() { return m_window; };
	void draw(sf::Sprite* p_sprite);

	/* VIEW */
	void createCameraView(int centerX, int centerY, int width, int height);
	sf::View*	getCameraView() { return m_cameraView; };

	/* CLOCK */
	sf::Clock	getMasterClock() { return m_masterClock; };
	float		getMasterClockSeconds() { return m_masterClock.getElapsedTime().asSeconds(); };

	/* ENTITY */
	void loadTexture(const char* p_path);
	sf::Texture* getTexture(const char* p_texturePath) { return  m_textureMap[p_texturePath]; };
	int createSprite(const char* p_texturePath, float p_scale, bool p_centerOrigin);
	int createSprite(const char* p_texturePath, float p_scale, bool p_centerOrigin, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY);
	sf::Sprite* getSprite(int p_spriteID) { return m_spriteVector[p_spriteID]; };
	void setSpriteFrame(int p_spriteID, int p_entity, int p_frame);

	/* MAP */

	/* COLLISION */
	bool checkCollision(int p_spriteID1, int p_spriteID2);


private:
	EngineManager();

	std::map<const char*, sf::Texture*> m_textureMap;
	std::map<const char*, sf::Texture*>::iterator m_textureMapIterator;
	std::vector<sf::Sprite*>	m_spriteVector;

	sf::RenderWindow*	m_window;
	sf::View*			m_cameraView;
	sf::Clock			m_masterClock;
	
	sf::Texture* mapTexture;
	sf::Sprite* mapSprite;

	/* MAP */

};
