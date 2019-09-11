#include "pch.h"
#include "potionMana.h"
#include "player.h"


PotionMana::PotionMana(const char* p_path, float p_posX, float p_posY, PotionType p_potionType) : Potion(p_path, p_posX, p_posY, p_potionType)
{
}


PotionMana::~PotionMana()
{
}

void PotionMana::setEffect(Player * p_player)
{
	p_player->increaseMana(25);
	m_efectUsed = true;
}
