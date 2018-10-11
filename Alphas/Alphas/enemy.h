#pragma once
#include "entity.h"

class Enemy : 
	public Entity
{
public:
	Enemy(float p_posX, float p_posY, float p_velocity, const char* p_path);
	~Enemy();

	void update(float p_deltaTime);


private:
	float m_velocity;
};