#include "pch.h"
#include "screenGameOver.h"
#include "buttonText.h"
#include "engineManager.h"
#include "screenManager.h"
#include "text.h"

#include "screenGameMode.h"
#include "screenMenuHome.h"

ScreenGameOver::ScreenGameOver()
{
	m_textGameOver = new Text("GAME OVER");
	m_textGameOver->setPosition(CenterTop);
	m_textGameOver->setSize(150);
	m_textGameOver->centerOrigin();

	m_buttonRetry = new ButtonText("RETRY", CenterList2_4);
	m_buttonVector.push_back(m_buttonRetry);

	m_buttonGoMenu = new ButtonText("MENU", CenterList3_4);
	m_buttonVector.push_back(m_buttonGoMenu);

	m_buttonRetry->setIsFocused(true);
}


ScreenGameOver::~ScreenGameOver()
{
	delete m_textGameOver;
	m_textGameOver = nullptr;

	for (int i = 0; i < m_buttonVector.size(); i++) {
		delete m_buttonVector[i];
		m_buttonVector[i] = nullptr;
	}

	m_buttonVector.clear();
}

void ScreenGameOver::init()
{
}

void ScreenGameOver::update(double p_time, double p_deltaTime)
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
			m_screenManager->changeScreen(new ScreenMenuHome());
	}
}

void ScreenGameOver::draw()
{
	m_textGameOver->draw();

	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}
}
