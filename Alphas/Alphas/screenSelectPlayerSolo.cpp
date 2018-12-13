#include "pch.h"
#include "screenSelectPlayerSolo.h"
#include "engineManager.h"
#include "screenManager.h"
#include "buttonText.h"
#include "buttonImage.h"
#include "image.h"

#include "screenGame.h"
#include "screenGameMode.h"


ScreenSelectPlayerSolo::ScreenSelectPlayerSolo()
{
	m_playerSelected = -1;

	m_buttonBlue = new ButtonImage("assets/spritesheet.png", Entities::PLAYER1, Down_Left1_3);
	m_buttonVector.push_back(m_buttonBlue);

	m_buttonGreen = new ButtonImage("assets/spritesheet.png", Entities::PLAYER2, Down_Left2_3);
	m_buttonVector.push_back(m_buttonGreen);

	m_buttonYellow = new ButtonImage("assets/spritesheet.png", Entities::PLAYER2, Down_Left3_3);
	m_buttonVector.push_back(m_buttonYellow);

	m_buttonPlay = new ButtonText("PLAY", Down_right_up);
	m_buttonVector.push_back(m_buttonPlay);

	m_buttonBack = new ButtonText("BACK", Down_right);
	m_buttonVector.push_back(m_buttonBack);

	m_buttonBlue->setIsFocused(true);
	m_buttonPlay->setIsBlocked(true);

	m_imageCharacters = new Image("assets/spritesheet.png", Entities::PLAYER1, Center_left);

	m_arrayEntities[0] = static_cast<int>(Entities::PLAYER1);
	m_arrayEntities[1] = static_cast<int>(Entities::PLAYER2);
	m_arrayEntities[2] = static_cast<int>(Entities::PLAYER2);
}


ScreenSelectPlayerSolo::~ScreenSelectPlayerSolo()
{
	for (int i = 0; i < m_buttonVector.size(); i++) {
		delete m_buttonVector[i];
		m_buttonVector[i] = nullptr;
	}

	delete m_imageCharacters;
	m_imageCharacters = nullptr;

	m_buttonVector.clear();
}

void ScreenSelectPlayerSolo::updateImage()
{
	if (m_buttonFocused < 3)
		m_imageCharacters->changeFrame(m_arrayEntities[m_buttonFocused]);
	else if (m_playerSelected != -1)
		m_imageCharacters->changeFrame(m_arrayEntities[m_playerSelected]);
}

void ScreenSelectPlayerSolo::init()
{
}

void ScreenSelectPlayerSolo::update(double p_time, double p_deltaTime)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && m_buttonFocused != 0 && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_buttonVector[m_buttonFocused]->setIsFocused(false);
		m_buttonFocused--;
		m_buttonVector[m_buttonFocused]->setIsFocused(true);
		
		updateImage();
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && m_buttonFocused != m_buttonVector.size() - 1 && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_buttonVector[m_buttonFocused]->setIsFocused(false);
		m_buttonFocused++;
		m_buttonVector[m_buttonFocused]->setIsFocused(true);
		
		updateImage();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);

		if (m_buttonFocused == 0) {
			m_playerSelected = 0;
			m_buttonPlay->setIsBlocked(false);
		}
		else if (m_buttonFocused == 1) {
			m_playerSelected = 1;
			m_buttonPlay->setIsBlocked(false);
		}
		else if (m_buttonFocused == 2) {
			m_playerSelected = -1;
			m_buttonPlay->setIsBlocked(true);
		}
		else if (m_buttonFocused == 3 && !m_buttonPlay->getIsBlocked()) {
			Entities t_entitySelected = static_cast<Entities>(m_arrayEntities[m_playerSelected]);
			m_screenManager->changeScreen(new ScreenGame(t_entitySelected));
		}
		else if (m_buttonFocused == 4)
			m_screenManager->changeScreen(new ScreenGameMode());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_engineManager->getKeyReleased()) {
		m_engineManager->setKeyReleased(false);
		m_screenManager->changeScreen(new ScreenGameMode());
	}
}

void ScreenSelectPlayerSolo::draw()
{
	for (auto t_buttons : m_buttonVector) {
		t_buttons->draw();
	}
	m_imageCharacters->draw();
}
