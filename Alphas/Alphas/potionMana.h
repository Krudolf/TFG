#pragma once
#include "potion.h"

class Player;

class PotionMana :
	public Potion
{
public:
	PotionMana(const char* p_path, float p_posX, float p_posY, PotionType p_potionType);
	~PotionMana();

	void setEffect(Player* p_player);
};

