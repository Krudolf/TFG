#include "pch.h"
#include "potionDamage.h"
#include "player.h"


PotionDamage::PotionDamage(const char* p_path, float p_posX, float p_posY, PotionType p_potionType) : Potion(p_path, p_posX, p_posY, p_potionType)
{
	int t_random = rand() % 5;
	switch (t_random)
	{
		case 0:
			m_effectIncrease = 0.6;
			break;
		case 1:
			m_effectIncrease = 0.8;
			break;
		case 2:
			m_effectIncrease = 1.2;
			break;
		case 3:
			m_effectIncrease = 1.4;
			break;
		case 4:
			m_effectIncrease = 1.6;
			break;
	}

	m_effectDuration = 10.f;
}


PotionDamage::~PotionDamage()
{
}

void PotionDamage::setEffect(Player * p_player)
{
	p_player->increaseDamage(m_effectDuration, m_effectIncrease);
	m_efectUsed = true;
}
