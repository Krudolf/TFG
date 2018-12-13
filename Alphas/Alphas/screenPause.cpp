#include "pch.h"
#include "screenPause.h"
#include "buttonText.h"
#include "engineManager.h"
#include "screenManager.h"

#include "screenMenuHome.h"

ScreenPause::ScreenPause()
{
	m_buttonContinue = new ButtonText("CONTINUE", CenterList2_4);
	m_buttonVector.push_back(m_buttonContinue);

	m_buttonExitGame = new ButtonText("EXIT", CenterList3_4);
	m_buttonVector.push_back(m_buttonExitGame);

	m_buttonContinue->setIsFocused(true);
}


ScreenPause::~ScreenPause()
{
	for (int i = 0; i < m_buttonVector.size(); i++) {
		delete m_buttonVector[i];
		m_buttonVector[i] = nullptr;
	}

	m_buttonVector.clear();
}

void ScreenPause::init()
{
}

void ScreenPause::update(double p_time, double p_deltaTime)
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

		if (m_buttonFocused == 0) {
			//m_engineManager->resumeClock();
			m_screenManager->deleteOverlayScreen();
		}
		else if (m_buttonFocused == 1)
			m_screenManager->changeScreen(new ScreenMenuHome());
	}
}

void ScreenPause::draw()
{
	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}
}
