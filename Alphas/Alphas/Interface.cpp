#include "pch.h"
#include "interface.h"
#include "fillBar.h"
#include "color.h"
#include "playerInfo.h"
#include "waveSystem.h"
#include "engineManager.h"

#include <string>

Interface::Interface(Player* p_player1, Player* p_player2, WaveSystem* p_waveSystem)
{
	m_engineManager = &EngineManager::p();

	m_width = m_engineManager->getWidth();
	m_height = m_engineManager->getHeight();

	float t_sizeX = m_width*0.35;
	float t_sizeY = 100.f;

	float t_posX;
	if (p_player2 != nullptr)
		t_posX = (m_width * 0.25) - (t_sizeX / 2);
	else
		t_posX = (m_width * 0.5) - (t_sizeX / 2);

	float t_posY = m_height - t_sizeY;

	m_player1Info = new PlayerInfo(p_player1, t_posX, t_posY, t_sizeX, t_sizeY);

	if(p_player2 != nullptr){
		t_posX = (m_width * 0.75) - (t_sizeX / 2);
		m_player2Info = new PlayerInfo(p_player2, t_posX, t_posY, t_sizeX, t_sizeY);
	}

	m_waveSystem = p_waveSystem;

	m_waveRectangle.setSize({ t_sizeX / 2, t_sizeY-25 });
	m_waveRectangle.setPosition((m_width / 2), 0);
	m_waveRectangle.setOrigin(m_waveRectangle.getGlobalBounds().width / 2, 0);
	m_waveRectangle.setFillColor(sf::Color(76, 99, 112, 255));

	m_waveInfo.setFont(*m_engineManager->getFont());
	m_waveInfo.setCharacterSize(20);
	m_waveText = "Wave: "    + std::to_string(p_waveSystem->getWaveNumber()) +
				 "\nEnemy: " + std::to_string(p_waveSystem->getAliveEnemy());
	m_waveInfo.setString(m_waveText);
	m_waveInfo.setPosition((m_waveRectangle.getPosition().x - m_waveRectangle.getGlobalBounds().width/4), 10);
	m_waveInfo.setFillColor(sf::Color::Black);
}


Interface::~Interface()
{
	delete m_player1Info;
	m_player1Info = nullptr;

	if (m_player2Info != nullptr) {
		delete m_player2Info;
		m_player2Info = nullptr;
	}
}

void Interface::update()
{
	m_player1Info->update();

	if(m_player2Info != nullptr)
		m_player2Info->update();

	m_waveText = "Wave: " + std::to_string(m_waveSystem->getWaveNumber()) +
				 "\nEnemy: " + std::to_string(m_waveSystem->getAliveEnemy());
	m_waveInfo.setString(m_waveText);
}

void Interface::draw()
{
	m_engineManager->draw(m_waveRectangle);
	m_player1Info->draw();

	if(m_player2Info != nullptr)
		m_player2Info->draw();

	m_engineManager->draw(m_waveInfo);
}
