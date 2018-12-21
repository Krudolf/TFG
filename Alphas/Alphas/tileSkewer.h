#pragma once
#include "tile.h"

class TileSkewer :
	public Tile
{
public:
	TileSkewer(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid);
	~TileSkewer();

	void applyEffect(Entity* p_entity);
	void update(double p_time, double p_deltaTime);

private:
	bool	m_makeDamage;
	float	m_damage;

	float	m_elapsedTime;
	float	m_column;
};

