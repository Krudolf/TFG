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

	/* VIEW */
	void createCameraView(int centerX, int centerY, int width, int height);
	sf::View*	getCameraView() { return m_cameraView; };

	/* CLOCK */
	sf::Clock	getMasterClock() { return m_masterClock; };
	float		getMasterClockSeconds() { return m_masterClock.getElapsedTime().asSeconds(); };

	/* ENTITY */
	int loadTexture(const char* p_path);
	int createSprite(int p_textureID, float p_scale, bool p_centerOrigin);
	sf::CircleShape* getSprite(int p_spriteID) { return m_spriteVector[p_spriteID]; };
	void setSpriteFrame(int p_spriteID, int p_entity, int p_frame);

	bool checkCollision(int p_spriteID1, int p_spriteID2);

	/* MAP */
	void createMap();
	sf::Sprite* getMapSprite() { return mapSprite; };

private:
	EngineManager();

	std::vector<const char*>	m_textureNameVector;
	std::vector<sf::Texture*>	m_textureVector;
	std::vector<sf::CircleShape*>	m_spriteVector;

	sf::RenderWindow*	m_window;
	sf::View*			m_cameraView;
	sf::Clock			m_masterClock;
	
	sf::Texture* mapTexture;
	sf::Sprite* mapSprite;

};

