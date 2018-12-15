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
	void closeWindow();
	int getWidth() { return m_width; };
	int getHeight() { return m_height; };
	void draw(sf::Sprite* p_sprite);
	void draw(sf::RectangleShape p_rectangle);
	void draw(sf::Text p_text);
	void draw(sf::Sprite p_sprite);
	void drawCircle();

	void checkEvents();
	bool getKeyReleased() { return m_keyReleased; };
	void setKeyReleased(bool p_keyReleased) { m_keyReleased = p_keyReleased; };

	/* VIEW */
	void createCameraView(int centerX, int centerY, int width, int height);
	sf::View*	getCameraView() { return m_gameView; };
	void setTargetGameView(float p_posX, float p_posY);
	void useGameView();
	void useInterfaceView();

	/* CLOCK */
	float		updateMasterClock();
	float		getMasterClockSeconds();
	void		pauseClock();
	void		resumeClock();
	void		restartClock();

	/* ENTITY */
	void loadTexture(const char* p_path);
	sf::Texture* getTexture(const char* p_texturePath) { return  m_textureMap[p_texturePath]; };
	int createSprite(const char* p_texturePath, float p_scale, bool p_centerOrigin);
	int createSprite(const char* p_texturePath, float p_scale, bool p_centerOrigin, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY);
	sf::Sprite* getSprite(int p_spriteID) { return m_spriteVector[p_spriteID]; };
	void setSpriteFrame(int p_spriteID, int p_entity, int p_frame);
	void getDirection(double p_posEntity1X, double p_posentity1Y, double p_posEntity2X, double p_posEntity2Y, float& p_directionX, float& p_directionY);
	void createCircle(float p_posX, float p_posY, float p_radius);

	/* COLLISION */
	bool checkCollision(int p_spriteID1, int p_spriteID2);
	bool checkCollisionCircle(int p_spriteID);

	/* MENU */
	sf::Font* getFont() { return m_font; };

private:
	EngineManager();

	int		m_width;
	int		m_height;

	bool	m_keyReleased;

	std::map<const char*, sf::Texture*> m_textureMap;
	std::map<const char*, sf::Texture*>::iterator m_textureMapIterator;
	std::vector<sf::Sprite*>	m_spriteVector;

	sf::RenderWindow*	m_window;
	sf::View*			m_gameView;
	sf::View			m_interfaceView;
	sf::Clock			m_masterClock;
	
	sf::Texture* mapTexture;
	sf::Sprite* mapSprite;

	sf::Font*	m_font;

	sf::Time	m_masterTime;
	sf::Time	m_pauseTime;

	sf::CircleShape	m_circle;

};
