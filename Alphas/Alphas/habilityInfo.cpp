#include "pch.h"
#include "habilityInfo.h"
#include "engineManager.h"

#include <iostream>

HabilityInfo::HabilityInfo(float p_posX, float p_posY, float p_skillSize, Entities p_playerEntity, int p_numHability)
{
	m_engineManager = &EngineManager::p();

	m_path = "assets/habilitySheet.png";
	m_engineManager->loadTexture(m_path);

	int t_playerNum = static_cast<int>(p_playerEntity);

	int t_row		= p_numHability % 4;
	int t_column	= t_playerNum % 4;

	m_hability.setTexture(*m_engineManager->getTexture(m_path));
	m_hability.setTextureRect(sf::IntRect(p_skillSize * t_row, p_skillSize * t_column, p_skillSize, p_skillSize));
	m_hability.setOrigin(m_hability.getGlobalBounds().width / 2, m_hability.getGlobalBounds().height / 2);
	m_hability.setPosition(p_posX, p_posY);

	m_cooldown.setSize({ p_skillSize, p_skillSize });
	m_cooldown.setPosition(p_posX, p_posY + p_skillSize / 2);
	m_cooldown.setOrigin(m_hability.getGlobalBounds().width / 2, m_hability.getGlobalBounds().height);
	m_cooldown.setFillColor(sf::Color(200,200,200,150));
}


HabilityInfo::~HabilityInfo()
{
}

void HabilityInfo::update(float p_activationTime, float p_cooldownDuration, bool p_enoughMana)
{
	float t_time = m_engineManager->getMasterClockSeconds();
	float t_remainingTime = (p_activationTime + p_cooldownDuration) - t_time;
	
	float t_cooldownNormalized = 0.f;
	if (t_remainingTime > 0) {
		t_cooldownNormalized = t_remainingTime / p_cooldownDuration;
		m_cooldown.setFillColor(sf::Color(200, 200, 200, 150));
	}
	else if (!p_enoughMana) {
		m_cooldown.setFillColor(sf::Color(30, 100, 250, 200));
		t_cooldownNormalized = 1.f;
	}
	else if (p_enoughMana)
		m_cooldown.setFillColor(sf::Color(200, 200, 200, 150));


	m_cooldown.setScale(1.f, t_cooldownNormalized);
}

void HabilityInfo::draw()
{
	m_engineManager->draw(m_hability);
	m_engineManager->draw(m_cooldown);
}
