#pragma once
#include "tile.h"

class TileBlock :
	public Tile
{
public:
	TileBlock(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid);
	~TileBlock();

	void applyEffect(Entity* p_entity);
};

