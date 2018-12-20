#pragma once
#include "tile.h"

class TileSkewer :
	public Tile
{
public:
	TileSkewer(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid);
	~TileSkewer();

	void applyEffect(Entity* p_entity);

private:
	float	m_damage;
};

