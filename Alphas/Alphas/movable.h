#pragma once

class Movable
{
public:
	Movable();
	~Movable();

	virtual void move() = 0;
};

