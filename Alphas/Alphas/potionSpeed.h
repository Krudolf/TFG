#pragma once
#include "potion.h"

class Player;

class PotionSpeed :
	public Potion
{
public:
	PotionSpeed(const char* p_path, float p_posX, float p_posY, PotionType p_potionType);
	~PotionSpeed();
	
	void setEffect(Player* p_player);

};