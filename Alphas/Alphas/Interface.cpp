#include "pch.h"
#include "interface.h"
#include "fillBar.h"
#include "color.h"
#include "playerInfo.h"

#include "engineManager.h"

Interface::Interface(Player* p_player1, Player* p_player2)
{
	m_engineManager = &EngineManager::p();

	m_width = m_engineManager->getWidth();
	m_height = m_engineManager->getHeight();

	float t_sizeX = 200.0f;
	float t_sizeY = 225.0f;

	float t_posX = 0;
	float t_posY = m_height - t_sizeY;

	m_player1Info = new PlayerInfo(p_player1, t_posX, t_posY, t_sizeX, t_sizeY);

	if(p_player2 != nullptr){
		t_posX = m_width - t_sizeX;
		m_player2Info = new PlayerInfo(p_player2, t_posX, t_posY, t_sizeX, t_sizeY);
	}
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
}

void Interface::draw()
{
	m_player1Info->draw();

	if(m_player2Info != nullptr)
		m_player2Info->draw();
}
