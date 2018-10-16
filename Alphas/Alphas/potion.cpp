#include "pch.h"
#include "potion.h"
#include "engineManager.h"
#include "player.h"


Potion::Potion(const char* p_path, float p_posX, float p_posY, PotionType p_potionType) : Entity(p_path, Entities::POTION)
{
	m_posX = p_posX;
	m_posY = p_posY;
	m_efectUsed = false;

	int t_frame = static_cast<int>(p_potionType);
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, t_frame);
	m_engineManager->getSprite(m_spriteID)->setPosition(m_posX, m_posY);
}


Potion::~Potion()
{

}

