#pragma once
#include "player.h"

class PlayerYellow :
	public Player
{
public:
	PlayerYellow(float p_posX, float p_posY, const char* p_path);
	~PlayerYellow();

	void levelStats();

	void hability1();
	void hability2();
	void hability3();

	void updateHability3() override;
};

