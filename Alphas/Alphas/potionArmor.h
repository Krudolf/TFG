#pragma once
#include "potion.h"

class PotionArmor :
	public Potion
{
public:
	PotionArmor(const char* p_path, float p_posX, float p_posY, PotionType p_potionType);
	~PotionArmor();

	void setEffect(Player* p_player);

};

