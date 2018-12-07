#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class EngineManager;
class Player;
class FillBar;
class HabilityInfo;
class StatsInfo;

class PlayerInfo
{
public:
	PlayerInfo(Player* p_owner, float p_posX, float p_posY, float p_sizeX, float p_sizeY);
	~PlayerInfo();

	void update();
	void draw();

private:
	EngineManager*	m_engineManager;

	Player*	m_owner;

	sf::RectangleShape	m_mainBox;

	FillBar*		m_healthBar;
	FillBar*		m_manaBar;

	HabilityInfo*	m_hability1;
	HabilityInfo*	m_hability2;
	HabilityInfo*	m_hability3;

	StatsInfo*		m_damageInfo;
	StatsInfo*		m_armorInfo;
	StatsInfo*		m_attackSpeedInfo;
	StatsInfo*		m_velocityInfo;
};

