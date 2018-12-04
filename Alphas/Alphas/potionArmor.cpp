#include "pch.h"
#include "potionArmor.h"
#include "player.h"

PotionArmor::PotionArmor(const char* p_path, float p_posX, float p_posY, PotionType p_potionType) : Potion(p_path, p_posX, p_posY, p_potionType)
{
	int t_random = rand() % 5;
	switch (t_random)
	{
	case 0:
		m_effectIncrease = 1.1;
		break;
	case 1:
		m_effectIncrease = 1.2;
		break;
	case 2:
		m_effectIncrease = 1.3;
		break;
	case 3:
		m_effectIncrease = 1.4;
		break;
	case 4:
		m_effectIncrease = 1.5;
		break;
	}

	m_effectDuration = 10.f;
}


PotionArmor::~PotionArmor()
{
}

void PotionArmor::setEffect(Player * p_player)
{
	p_player->increaseArmor(m_effectDuration, m_effectIncrease);
	m_efectUsed = true;
}