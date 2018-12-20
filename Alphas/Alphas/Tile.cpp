#include "pch.h"
#include "tile.h"


Tile::Tile(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid) : Entity(p_urlTexture, p_textureLeft, p_textureTop, p_textureWidth, p_textureHeight, p_posX, p_posY)
{
	m_tileType = TileTypes::GROUND;
	m_gid = p_gid;
}


Tile::~Tile()
{
}

void Tile::applyEffect(Entity * p_entity)
{
}

void Tile::update(double p_time, double p_deltaTime)
{
}
