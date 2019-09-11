#pragma once
#include "entity.h"
#include "tileTypes_enum.h"

class Tile : 
	public Entity
{
public:
	Tile(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid);
	virtual ~Tile();

	virtual void applyEffect(Entity* p_entity);
	virtual void update(double p_time, double p_deltaTime);

	int			getGID() { return m_gid; };
	TileTypes	getTileType() { return m_tileType; };

protected:
	TileTypes	m_tileType;
	int m_gid;

};