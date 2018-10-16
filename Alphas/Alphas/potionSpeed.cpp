#include "pch.h"
#include "potionSpeed.h"
#include "player.h"


PotionSpeed::PotionSpeed(const char* p_path, float p_posX, float p_posY, PotionType p_potionType) : Potion(p_path, p_posX, p_posY, p_potionType)
{
}


PotionSpeed::~PotionSpeed()
{
}

void PotionSpeed::setEffect(Player * p_player)
{
	p_player->increaseSpeed(10); //Time in seconds of speed increase
	m_efectUsed = true;
}

