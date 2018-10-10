#pragma once
#include "entity.h"

class Entity;

class Player :
	public Entity
{
public:
	Player();
	~Player();
	
	void move(float p_delteTime);
	void update(float p_deltaTime);

private:
	int m_velocity;
};

