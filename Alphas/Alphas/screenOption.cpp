#include "pch.h"
#include "screenOption.h"
#include "engineManager.h"
#include "screenManager.h"
#include "screenMenuHome.h"
#include "button.h"
#include "buttonText.h"
#include "text.h"
#include "image.h"


ScreenOption::ScreenOption()
{
	m_textAlphas = new Text("ALPHAS");
	m_textAlphas->setPosition(CenterTop);
	m_textAlphas->setSize(150);
	m_textAlphas->centerOrigin();

	m_buttonPlay = new ButtonText("JUGAR", LeftList1_3);
	m_buttonVector.push_back(m_buttonPlay);

	m_buttonOptions = new ButtonText("CONTROLES", LeftList2_3);
	m_buttonVector.push_back(m_buttonOptions);

	m_buttonQuit = new ButtonText("SALIR", LeftList3_3);
	m_buttonVector.push_back(m_buttonQuit);

	m_buttonOptions->setIsFocused(true);

	m_keyboardImage		= new Image("assets/keyboard.png", RightList1_3);
	m_keyboardImage->setScale(0.5, 0.5);

	m_controllerImage	= new Image("assets/controller.png", RightList3_3);
	m_controllerImage->setScale(0.5, 0.5);
}


ScreenOption::~ScreenOption()
{
	delete m_textAlphas;
	m_textAlphas = nullptr;

	delete m_keyboardImage;
	m_keyboardImage = nullptr;

	delete m_controllerImage;
	m_controllerImage = nullptr;

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_screenManager->changeScreen(new ScreenMenuHome());
	}
}

void ScreenOption::draw()
{
	m_textAlphas->draw();

	m_keyboardImage->draw();
	m_controllerImage->draw();

	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}
}
