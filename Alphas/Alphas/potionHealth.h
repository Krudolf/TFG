#pragma once
#include "potion.h"

class Player;

class PotionHealth :
	public Potion
{
public:
	PotionHealth(const char* p_path, float p_posX, float p_posY, PotionType p_potionType);
	~PotionHealth();

	void setEffect(Player* p_player);

};

