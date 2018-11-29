#pragma once
#include "potion.h"

class PotionDamage :
	public Potion
{
public:
	PotionDamage(const char* p_path, float p_posX, float p_posY, PotionType p_potionType);
	~PotionDamage();

	void setEffect(Player* p_player);
};

