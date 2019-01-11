#include "pch.h"
#include "interface.h"
#include "fillBar.h"
#include "color.h"
#include "playerInfo.h"
#include "waveSystem.h"
#include "engineManager.h"
#include "image.h"

#include <string>

Interface::Interface(Player* p_player1, Player* p_player2, WaveSystem* p_waveSystem)
{
	m_engineManager = &EngineManager::p();

	m_width = m_engineManager->getWidth();
	m_height = m_engineManager->getHeight();

	float t_posX;
	if (p_player2 != nullptr)
		t_posX = (m_width * 0.25);
	else
		t_posX = (m_width * 0.5);

	float t_posY = m_height;

	m_player1Info = new PlayerInfo(p_player1, t_posX, t_posY);

	if(p_player2 != nullptr){
		t_posX = (m_width * 0.75);
		m_player2Info = new PlayerInfo(p_player2, t_posX, t_posY);
	}

	m_waveSystem = p_waveSystem;
	
	m_waveBox = new Image("assets/waveBox.png", { 0, 0 });
	Point t_pos = { m_width / 2, m_waveBox->getHeight() / 2 };
	m_waveBox->setPosition(t_pos);

	m_waveInfo.setFont(*m_engineManager->getFont());
	m_waveInfo.setCharacterSize(20);
	m_waveText = "Wave: "    + std::to_string(p_waveSystem->getWaveNumber()) +
				 "\nEnemy: " + std::to_string(p_waveSystem->getAliveEnemy());
	m_waveInfo.setString(m_waveText);
	m_waveInfo.setPosition(t_pos.x, t_pos.y);
	m_waveInfo.setOrigin(m_waveInfo.getGlobalBounds().width / 2, m_waveInfo.getGlobalBounds().height / 2 + 7.5f);
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

	delete m_waveBox;
	m_waveBox = nullptr;
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
	m_waveBox->draw();
	m_engineManager->draw(m_waveInfo);

	m_player1Info->draw();

	if(m_player2Info != nullptr)
		m_player2Info->draw();

}
