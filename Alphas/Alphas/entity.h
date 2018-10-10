#pragma once

class EngineManager;

class Entity
{
public:
	Entity();
	~Entity();

	virtual void update(float p_deltaTime);
	void draw();

	float getPositionX() { return m_posX; };
	float getPositionY() { return m_posY; };

protected:
	EngineManager*	m_engineManager;

	int m_textureID;
	int m_spriteID;

	float m_lastPosX, m_lastPosY;
	float m_posX, m_posY;
};

