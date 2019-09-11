#include "pch.h"
#include "screenSelectPlayerCooperative.h"
#include "engineManager.h"
#include "screenManager.h"
#include "buttonText.h"
#include "buttonImage.h"
#include "image.h"
#include "joystick_enum.h"

#include "screenGame.h"
#include "screenGameMode.h"


ScreenSelectPlayerCooperative::ScreenSelectPlayerCooperative()
{
	m_joystickReleased = true;

	m_playerSelected1 = -1;
	m_playerSelected2 = -1;

	m_buttonBlue1 = new ButtonImage("assets/spritesheet.png", Entities::PLAYER_BLUE, Down_Left1_3);
	m_buttonVector1.push_back(m_buttonBlue1);

	m_buttonGreen1 = new ButtonImage("assets/spritesheet.png", Entities::PLAYER_GREEN, Down_Left2_3);
	m_buttonVector1.push_back(m_buttonGreen1);

	m_buttonYellow1 = new ButtonImage("assets/spritesheet.png", Entities::PLAYER_YELLOW, Down_Left3_3);
	m_buttonVector1.push_back(m_buttonYellow1);


	m_buttonBlue2 = new ButtonImage("assets/spritesheet.png", Entities::PLAYER_BLUE, Down_Right1_3);
	m_buttonVector2.push_back(m_buttonBlue2);

	m_buttonGreen2 = new ButtonImage("assets/spritesheet.png", Entities::PLAYER_GREEN, Down_Right2_3);
	m_buttonVector2.push_back(m_buttonGreen2);

	m_buttonYellow2 = new ButtonImage("assets/spritesheet.png", Entities::PLAYER_YELLOW, Down_Right3_3);
	m_buttonVector2.push_back(m_buttonYellow2);

	//-----------
	m_buttonBack = new ButtonText("BACK", Down_right);
	m_buttonVector1.push_back(m_buttonBack);
	
	m_buttonPlay = new ButtonText("PLAY", Down_right_up);
	m_buttonVector1.push_back(m_buttonPlay);

	//-----------
	m_buttonBlue1->setIsFocused(true);
	m_buttonBlue2->setIsFocused(true);
	m_buttonPlay->setIsBlocked(true);

	m_imageCharacters1 = new Image("assets/spritesheet.png", Entities::PLAYER_BLUE, Center_left);
	m_imageCharacters2 = new Image("assets/spritesheet.png", Entities::PLAYER_BLUE, Center_right);

	m_arrayEntities[0] = static_cast<int>(Entities::PLAYER_BLUE);
	m_arrayEntities[1] = static_cast<int>(Entities::PLAYER_GREEN);
	m_arrayEntities[2] = static_cast<int>(Entities::PLAYER_YELLOW);
}


ScreenSelectPlayerCooperative::~ScreenSelectPlayerCooperative()
{
	for (int i = 0; i < m_buttonVector1.size(); i++) {
		delete m_buttonVector1[i];
		m_buttonVector1[i] = nullptr;
	}

	for (int i = 0; i < m_buttonVector2.size(); i++) {
		delete m_buttonVector2[i];
		m_buttonVector2[i] = nullptr;
	}

	delete m_imageCharacters1;
	m_imageCharacters1 = nullptr;

	delete m_imageCharacters2;
	m_imageCharacters2 = nullptr;

	m_buttonVector1.clear();
	m_buttonVector2.clear();
}

void ScreenSelectPlayerCooperative::updateImage()
{
	if (m_buttonFocused1 < 3)
		m_imageCharacters1->changeFrame(m_arrayEntities[m_buttonFocused1]);
	else if (m_playerSelected1 != -1)
		m_imageCharacters1->changeFrame(m_arrayEntities[m_playerSelected1]);

	if (m_buttonFocused2 < 3)
		m_imageCharacters2->changeFrame(m_arrayEntities[m_buttonFocused2]);
	else if (m_playerSelected2 != -1)
		m_imageCharacters2->changeFrame(m_arrayEntities[m_playerSelected2]);
}

void ScreenSelectPlayerCooperative::updatePlayer1()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && m_buttonFocused1 != 0 && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_buttonVector1[m_buttonFocused1]->setIsFocused(false);
		m_buttonFocused1--;
		m_buttonVector1[m_buttonFocused1]->setIsFocused(true);

		updateImage();
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && m_buttonFocused1 != m_buttonVector1.size() - 1 && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_buttonVector1[m_buttonFocused1]->setIsFocused(false);
		m_buttonFocused1++;
		m_buttonVector1[m_buttonFocused1]->setIsFocused(true);

		updateImage();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);

		if (m_buttonFocused1 == 0) {
			m_playerSelected1 = 0;
		}
		else if (m_buttonFocused1 == 1) {
			m_playerSelected1 = 1;
		}
		else if (m_buttonFocused1 == 2) {
			m_playerSelected1 = 2;
		}
		else if (m_buttonFocused1 == 3)
			m_screenManager->changeScreen(new ScreenGameMode());
		else if (m_buttonFocused1 == 4 && !m_buttonPlay->getIsBlocked()) {
			Entities t_entitySelected1 = static_cast<Entities>(m_arrayEntities[m_playerSelected1]);
			Entities t_entitySelected2 = static_cast<Entities>(m_arrayEntities[m_playerSelected2]);
			m_screenManager->changeScreen(new ScreenGame(t_entitySelected1, t_entitySelected2));
		}

		int i = 0;
		for (auto t_button : m_buttonVector1) {
			if (i == m_playerSelected1)
				t_button->select();
			else
				t_button->unselect();
			i++;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_screenManager->changeScreen(new ScreenGameMode());
	}
}

void ScreenSelectPlayerCooperative::updatePlayer2()
{
	if (sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_Y) <= -75 && m_buttonFocused2 != 0 && m_joystickReleased) {
		m_joystickReleased = false;
		m_buttonVector2[m_buttonFocused2]->setIsFocused(false);
		m_buttonFocused2--;
		m_buttonVector2[m_buttonFocused2]->setIsFocused(true);

		updateImage();
	}
	else if (sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_Y) >= 75 && m_buttonFocused2 != m_buttonVector2.size() - 1 && m_joystickReleased) {
		m_joystickReleased = false;
		m_buttonVector2[m_buttonFocused2]->setIsFocused(false);
		m_buttonFocused2++;
		m_buttonVector2[m_buttonFocused2]->setIsFocused(true);

		updateImage();
	}

	if (sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_Y) >= -1 && sf::Joystick::getAxisPosition(0, (sf::Joystick::Axis)JoystickPad::LEFT_Y) <= 1)
		m_joystickReleased = true;

	if (sf::Joystick::isButtonPressed(0, (int)JoystickButton::A)) {
		if (m_buttonFocused2 == 0) {
			m_playerSelected2 = 0;
		}
		else if (m_buttonFocused2 == 1) {
			m_playerSelected2 = 1;
		}
		else if (m_buttonFocused2 == 2) {
			m_playerSelected2 = 2;
		}

		int i = 0;
		for (auto t_button : m_buttonVector2) {
			if (i == m_playerSelected2)
				t_button->select();
			else
				t_button->unselect();
			i++;
		}
	}
}

void ScreenSelectPlayerCooperative::init()
{
}

void ScreenSelectPlayerCooperative::update(double p_time, double p_deltaTime)
{
	if (m_playerSelected1 != -1 && m_playerSelected2 != -1 && m_buttonPlay->getIsBlocked())
		m_buttonPlay->setIsBlocked(false);

	updatePlayer1();
	updatePlayer2();
}

void ScreenSelectPlayerCooperative::draw()
{
	for (auto t_buttons : m_buttonVector1) {
		t_buttons->draw();
	}

	for (auto t_buttons : m_buttonVector2) {
		t_buttons->draw();
	}

	m_imageCharacters1->draw();
	m_imageCharacters2->draw();
}
