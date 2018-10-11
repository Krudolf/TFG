#pragma once

class EngineManager;

enum class Entities {
	PLAYER1 = 0,
	BULLET1,
	PLAYER2,
	BULLET2,
	ENEMY,
	ITEM
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
	Entity(const char* p_path, Entities p_ent);
	Entity(int p_textureID, Entities p_ent);
	virtual ~Entity();

	virtual void update(float p_deltaTime);
	virtual void draw();

	float	getPositionX() { return m_posX; };
	float	getPositionY() { return m_posY; };
	int		getSpriteID()  { return m_spriteID; };


protected:
	EngineManager*	m_engineManager;

	int m_textureID;
	int m_spriteID;

	int m_spriteSheetRow;

	float m_posX, m_posY;
	float m_lastPosX, m_lastPosY;
};

