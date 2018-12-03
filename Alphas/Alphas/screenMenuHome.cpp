#include "pch.h"
#include "screenMenuHome.h"
#include "engineManager.h"
#include "screenManager.h"
#include "screenGameMode.h"
#include "screenOption.h"
#include "button.h"

#include <iostream>

ScreenMenuHome::ScreenMenuHome() : Screen()
{
	m_buttonPlay	= new Button("PLAY", CenterList1_3);
	m_buttonVector.push_back(m_buttonPlay);

	m_buttonOptions	= new Button("OPTIONS", CenterList2_3);
	m_buttonVector.push_back(m_buttonOptions);

	m_buttonQuit	= new Button("EXIT", CenterList3_3);
	m_buttonVector.push_back(m_buttonQuit);
	
	m_buttonPlay->setIsFocused(true);
}


ScreenMenuHome::~ScreenMenuHome()
{
	for (int i = 0; i < m_buttonVector.size(); i++) {
		delete m_buttonVector[i];
		m_buttonVector[i] = nullptr;
	}

	m_buttonVector.clear();
}

void ScreenMenuHome::init()
{
}

void ScreenMenuHome::update(double p_time, double p_deltaTime)
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
			m_screenManager->changeScreen(new ScreenGameMode());
		else if (m_buttonFocused == 1)
			m_screenManager->changeScreen(new ScreenOption());
		else if (m_buttonFocused == 2)
			m_engineManager->closeWindow();
	}
}

void ScreenMenuHome::draw()
{
	m_engineManager->getWindow()->clear(sf::Color::Green);

	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}

	m_engineManager->getWindow()->display();
}
