#pragma once
#include "entity.h"

enum class PotionType {
	HEALTH,
	MANA,
	SPEED,
	DAMAGE,
	ARMOR,
	ATACK_SPEED
};

class Player;

class Potion :
	public Entity
{
public:
	Potion(const char* p_path, float p_posX, float p_posY, PotionType p_potionType);
	virtual ~Potion();

	virtual void setEffect(Player* p_player) = 0;
	bool getEffectUsed() { return m_efectUsed; };

protected:
	bool m_efectUsed;

	float	m_effectIncrease;
	float	m_effectDuration;

};