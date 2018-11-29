#pragma once
#include "potion.h"

class PotionAtackSpeed :
	public Potion
{
public:
	PotionAtackSpeed(const char* p_path, float p_posX, float p_posY, PotionType p_potionType);
	~PotionAtackSpeed();
	
	void setEffect(Player* p_player);
};

