#include "pch.h"
#include "screenGameMode.h"
#include "engineManager.h"
#include "screenManager.h"
#include "button.h"
#include "buttonText.h"
#include "screenMenuHome.h"
#include "screenSelectPlayerSolo.h"
#include "screenSelectPlayerCooperative.h"
#include "text.h"

#include <iostream>

ScreenGameMode::ScreenGameMode()
{
	m_textAlphas = new Text("ALPHAS");
	m_textAlphas->setPosition(CenterTop);
	m_textAlphas->setSize(150);
	m_textAlphas->centerOrigin();

	m_buttonPlay = new ButtonText("PLAY", LeftList1_3);
	m_buttonVectorStatic.push_back(m_buttonPlay);

	m_buttonOptions = new ButtonText("OPTIONS", LeftList2_3);
	m_buttonVectorStatic.push_back(m_buttonOptions);

	m_buttonQuit = new ButtonText("EXIT", LeftList3_3);
	m_buttonVectorStatic.push_back(m_buttonQuit);

	m_buttonPlay->setIsFocused(true);

	m_buttonSolo = new ButtonText("SOLO", RightList1_3);
	m_buttonVector.push_back(m_buttonSolo);

	m_buttonCooperative = new ButtonText("COOPERATIVO", RightList2_3);
	m_buttonVector.push_back(m_buttonCooperative);

	m_buttonSolo->setIsFocused(true);
}


ScreenGameMode::~ScreenGameMode()
{
	delete m_textAlphas;
	m_textAlphas = nullptr;

	for (int i = 0; i < m_buttonVector.size(); i++) {
		delete m_buttonVector[i];
		m_buttonVector[i] = nullptr;
	}

	m_buttonVector.clear();
}

void ScreenGameMode::init()
{
}

void ScreenGameMode::update(double p_time, double p_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_buttonFocused != 0 && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_buttonVector[m_buttonFocused]->setIsFocused(false);
		m_buttonFocused--;
		m_buttonVector[m_buttonFocused]->setIsFocused(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_buttonFocused != m_buttonVector.size() - 1 && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_buttonVector[m_buttonFocused]->setIsFocused(false);
		m_buttonFocused++;
		m_buttonVector[m_buttonFocused]->setIsFocused(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);

		if (m_buttonFocused == 0)
			m_screenManager->changeScreen(new ScreenSelectPlayerSolo());
		else if (m_buttonFocused == 1 && !m_buttonCooperative->getIsBlocked())
			m_screenManager->changeScreen(new ScreenSelectPlayerCooperative());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_screenManager->changeScreen(new ScreenMenuHome());
	}
}

void ScreenGameMode::draw()
{
	m_textAlphas->draw();

	for (auto t_buttons : m_buttonVectorStatic) {
		t_buttons->draw();
	}

	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}
}
