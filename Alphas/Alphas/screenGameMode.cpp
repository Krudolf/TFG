#include "pch.h"
#include "screenGameMode.h"
#include "engineManager.h"
#include "screenManager.h"
#include "screenGame.h"
#include "screenMenuHome.h"
#include "button.h"

#include <iostream>

ScreenGameMode::ScreenGameMode()
{
	m_buttonSolo = new Button("SOLO", CenterList1_4);
	m_buttonVector.push_back(m_buttonSolo);

	m_buttonCooperativeAI = new Button("COOP: AI", CenterList2_4);
	m_buttonVector.push_back(m_buttonCooperativeAI);

	m_buttonCooperativeLocal = new Button("COOP: LOCAL", CenterList3_4);
	m_buttonVector.push_back(m_buttonCooperativeLocal);

	m_buttonBack = new Button("BACK", CenterList4_4);
	m_buttonVector.push_back(m_buttonBack);

	m_buttonSolo->setIsFocused(true);
}


ScreenGameMode::~ScreenGameMode()
{
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
			m_screenManager->changeScreen(new ScreenGame());
		else if (m_buttonFocused == 1)
			std::cout << "COOPERATIVE: AI" << std::endl;
		else if (m_buttonFocused == 2)
			std::cout << "COOPERATIVE: LOCAL" << std::endl;
		else if (m_buttonFocused == 3)
			m_screenManager->changeScreen(new ScreenMenuHome());
	}
}

void ScreenGameMode::draw()
{
	m_engineManager->getWindow()->clear(sf::Color::Green);

	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}

	m_engineManager->getWindow()->display();
}
