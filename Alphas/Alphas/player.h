#pragma once
#include "entity.h"
#include "movable.h"


class Player :
	public Entity, public Movable
{
public:
	Player(sf::RenderWindow* p_window);
	~Player();
	
	void move();
	void update();
};

