#pragma once
#include "stats_enum.h"

#include <functional>
#include <string>
#include <SFML/Graphics/Text.hpp>

class EngineManager;
class Image;
class Player;

class StatsInfo
{
public:
	StatsInfo(Stats p_stats, Player* p_owner, float p_posX, float p_posY);
	~StatsInfo();

	void update();
	void draw();

private:
	EngineManager*	m_engineManager;

	Image*		m_statIcon;
	sf::Text	m_statNumber;

	Player*		m_owner;

	//std::function<float()> getStatValue;
	std::function<float(Player*)> getStatValue;

};

