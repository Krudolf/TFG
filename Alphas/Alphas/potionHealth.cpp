#include "pch.h"
#include "potionHealth.h"
#include "player.h"

PotionHealth::PotionHealth(const char* p_path, float p_posX, float p_posY, PotionType p_potionType) : Potion(p_path,p_posX, p_posY, p_potionType)
{

}


PotionHealth::~PotionHealth()
{

}

void PotionHealth::setEffect(Player * p_player)
{
	p_player->increaseHealth(25);
	m_efectUsed = true;
}
