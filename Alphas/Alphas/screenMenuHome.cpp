#include "pch.h"
#include "screenMenuHome.h"
#include "engineManager.h"
#include "screenManager.h"
#include "screenGameMode.h"
#include "screenOption.h"
#include "button.h"
#include "buttonText.h"
#include "text.h"
#include "image.h"


ScreenMenuHome::ScreenMenuHome() : Screen()
{
	m_textAlphas = new Text("ALPHAS");
	m_textAlphas->setPosition(CenterTop);
	m_textAlphas->setSize(150);
	m_textAlphas->centerOrigin();

	m_buttonPlay	= new ButtonText("JUGAR", LeftList1_3);
	m_buttonVector.push_back(m_buttonPlay);

	m_buttonOptions	= new ButtonText("CONTROLES", LeftList2_3);
	m_buttonVector.push_back(m_buttonOptions);

	m_buttonQuit	= new ButtonText("SALIR", LeftList3_3);
	m_buttonVector.push_back(m_buttonQuit);

	int t_num = rand() % 3;
	m_playerImage = new Image("assets/spritesheet.png", RightList2_3);
	m_playerImage->setTextureRect(128, t_num, true);
	m_playerImage->setScale(2, 2);
	
	m_buttonPlay->setIsFocused(true);
}


ScreenMenuHome::~ScreenMenuHome()
{
	delete m_textAlphas;
	m_textAlphas = nullptr;

	delete m_playerImage;
	m_playerImage = nullptr;

	for (int i = 0; i < m_buttonVector.size(); i++) {
		delete m_buttonVector[i];
		m_buttonVector[i] = nullptr;
	}

	m_buttonVector.clear();
}

void ScreenMenuHome::init()
{
	m_engineManager->useInterfaceView();
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_engineManager->closeWindow();
	}
}

void ScreenMenuHome::draw()
{
	m_textAlphas->draw();

	m_playerImage->draw();

	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}
}
