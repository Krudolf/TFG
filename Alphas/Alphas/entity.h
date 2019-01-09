#pragma once
#include "entities_enum.h"
#include <vector>

class EngineManager;
class HashGrid;

enum class Direction {
	RIGHT = 0,
	LEFT,
	UP,
	DOWN,
	RIGHT_UP,
	RIGHT_DOWN,
	LEFT_UP,
	LEFT_DOWN,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
	NONE
};

enum class ProjectileType {
	STRAIGHT = 0,
	SPIN,
	STRAIGHT_SPIN,
	CONUS
};

class Entity
{
public:
	Entity(const char* p_path, Entities p_entity);
	Entity(const char* p_path, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY);
	virtual ~Entity();

	virtual void update();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

	double	getPositionX()	{ return m_posX; };
	double	getPositionY()	{ return m_posY; };
	float	getWidth()		{ return m_width; };
	float	getHeight()		{ return m_height; };
	int		getSpriteID()	{ return m_spriteID; };
	
	const char* getTexturePath()	{ return m_texturePath; };
	Entities	getEntity()			{ return m_entity; };
	
	void	setNearEntityVector(std::vector<Entity*> p_nearEntity) { m_nearEntityVector = p_nearEntity; };

protected:
	EngineManager*	m_engineManager;
	Entities	m_entity;

	HashGrid*	m_hashGrid;
	std::vector<Entity*>	m_nearEntityVector;

	const char*	m_texturePath;

	int		m_spriteID;
	int		m_spriteSheetRow;

	double	m_posX;
	double	m_posY;
	double	m_lastPosX;
	double	m_lastPosY;

	float	m_width;
	float	m_height;
};

