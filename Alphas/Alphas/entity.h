#pragma once

class EngineManager;

enum class Entities {
	PLAYER1 = 0,
	BULLET1,
	PLAYER2,
	BULLET2,
	ENEMY,
	POTION
};

enum class Direction {
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class Entity
{
public:
	Entity(const char* p_path, Entities p_entity);
	Entity(const char* p_path, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY);
	virtual ~Entity();

	virtual void update();
	virtual void update(float p_deltaTime);
	virtual void draw();

	float	getPositionX() { return m_posX; };
	float	getPositionY() { return m_posY; };
	int		getSpriteID()  { return m_spriteID; };


protected:
	EngineManager*	m_engineManager;

	const char*	m_texturePath;

	int m_spriteID;
	int m_spriteSheetRow;

	float m_posX, m_posY;
	float m_lastPosX, m_lastPosY;
};

