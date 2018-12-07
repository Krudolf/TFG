#pragma once
#include "habilities_enum.h"

#include <SFML/Graphics.hpp>

class EngineManager;

class HabilityInfo
{
public:
	HabilityInfo(Hability p_hability, float p_posX, float p_posY, float p_skillSize);
	~HabilityInfo();

	void update(float p_activationTime, float p_cooldownDuration, bool p_enoughMana);
	void draw();

private:
	EngineManager*	m_engineManager;

	const char*		m_path;

	sf::Sprite		m_hability;
	sf::RectangleShape	m_cooldown;
};

