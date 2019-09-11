#include "pch.h"
#include "statsInfo.h"
#include "engineManager.h"
#include "image.h"
#include "player.h"

#include <sstream>
#include <cmath>


StatsInfo::StatsInfo(Stats p_stats, Player* p_owner, float p_posX, float p_posY)
{
	m_engineManager = &EngineManager::p();

	m_statIcon = new Image(p_stats, p_posX, p_posY);
	
	m_statNumber.setFont(*m_engineManager->getFont());
	m_statNumber.setCharacterSize(10);
	m_statNumber.setString(": XXX");
	m_statNumber.setPosition(p_posX + 15, p_posY - 5);
	m_statNumber.setFillColor(sf::Color::Black);

	m_owner = p_owner;

	switch (p_stats)
	{
	case Stats::DAMAGE:
		getStatValue = &Player::getDamage;
		break;
	case Stats::ARMOR:
		getStatValue = &Player::getArmor;
		break;
	case Stats::ATACK_SPEED:
		getStatValue = &Player::getAtackSpeed;
		break;
	case Stats::VELOCITY:
		getStatValue = &Player::getVelocity;
		break;
	}
}


StatsInfo::~StatsInfo()
{
	delete m_statIcon;
	m_statIcon = nullptr;
}

void StatsInfo::update()
{
	std::stringstream t_string;
	t_string.precision(1);
	t_string << std::fixed << getStatValue(m_owner);

	m_statNumber.setString(": " + t_string.str());
}

void StatsInfo::draw()
{
	m_statIcon->draw();
	m_engineManager->draw(m_statNumber);
}
