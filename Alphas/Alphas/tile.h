#pragma once

#include "entity.h"

class Tile : 
	public Entity
{
public:
	Tile(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid);
	~Tile();

	int getGID() { return m_gid; };

private:
	int m_gid;
};