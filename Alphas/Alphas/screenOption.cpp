#include "pch.h"
#include "screenOption.h"
#include "engineManager.h"
#include "screenManager.h"
#include "screenMenuHome.h"
#include "button.h"


ScreenOption::ScreenOption()
{
	m_buttonFocused = 0;

	m_buttonBack = new Button("BACK", Down_right);
	m_buttonVector.push_back(m_buttonBack);

	m_buttonBack->setIsFocused(true);
}


ScreenOption::~ScreenOption()
{
	for (int i = 0; i < m_buttonVector.size(); i++) {
		delete m_buttonVector[i];
		m_buttonVector[i] = nullptr;
	}

	m_buttonVector.clear();
}

void ScreenOption::init()
{
}

void ScreenOption::update(double p_time, double p_deltaTime)
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
			m_screenManager->changeScreen(new ScreenMenuHome());
	}
		
}

void ScreenOption::draw()
{
	m_engineManager->getWindow()->clear(sf::Color::Green);

	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}

	m_engineManager->getWindow()->display();
}
