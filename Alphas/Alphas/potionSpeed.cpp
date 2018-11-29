#include "pch.h"
#include "potionSpeed.h"
#include "player.h"


PotionSpeed::PotionSpeed(const char* p_path, float p_posX, float p_posY, PotionType p_potionType) : Potion(p_path, p_posX, p_posY, p_potionType)
{
	int t_random = rand() % 5;
	switch (t_random)
	{
		case 0:
			m_effectIncrease = 0.5;
			break;
		case 1:
			m_effectIncrease = 0.75;
			break;
		case 2:
			m_effectIncrease = 1.25;
			break;
		case 3:
			m_effectIncrease = 1.5;
			break;
		case 4:
			m_effectIncrease = 1.75;
			break;
	}

	m_effectDuration = 10.f;
}


PotionSpeed::~PotionSpeed()
{
}

void PotionSpeed::setEffect(Player * p_player)
{
	p_player->increaseSpeed(m_effectDuration, m_effectIncrease);
	m_efectUsed = true;
}

