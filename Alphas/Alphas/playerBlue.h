#pragma once
#include "player.h"

class PlayerBlue :
	public Player
{
public:
	PlayerBlue(float p_posX, float p_posY, const char* p_path);
	~PlayerBlue();

	void hability1();
	void hability2();
	void hability3();
};

