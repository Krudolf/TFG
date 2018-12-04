#pragma once
#include "player.h"

class PlayerGreen :
	public Player
{
public:
	PlayerGreen(float p_posX, float p_posY, const char* p_path);
	~PlayerGreen();

	void hability1();
	void hability2();
	void hability3();
};

