#include "pch.h"
#include "screenManager.h"
#include "engineManager.h"
#include "screen.h"

ScreenManager::ScreenManager()
{
	m_engineManager = &EngineManager::p();

	m_currentScreen = nullptr;
	m_overlayScreen = nullptr;
}


ScreenManager::~ScreenManager()
{
	if (m_currentScreen != nullptr) {
		delete m_currentScreen;
		m_currentScreen = nullptr;
	}

	if (m_overlayScreen != nullptr) {
		delete m_overlayScreen;
		m_overlayScreen = nullptr;
	}
}

ScreenManager & ScreenManager::p()
{
	static ScreenManager instance;

	return instance;
}

void ScreenManager::deleteOverlayScreen()
{
	if (m_overlayScreen != nullptr) {
		delete m_overlayScreen;
		m_overlayScreen = nullptr;
	}
}

bool ScreenManager::overlayOpened()
{
	if (m_overlayScreen != nullptr)
		return true;
	else
		return false;
}

void ScreenManager::init()
{
	m_currentScreen->init();
}

void ScreenManager::update(double p_time, double p_deltaTime)
{
	if (m_overlayScreen != nullptr)
		m_overlayScreen->update(p_time, p_deltaTime);
	else
		m_currentScreen->update(p_time, p_deltaTime);
}

void ScreenManager::draw()
{
	m_engineManager->getWindow()->clear(sf::Color(27,55,86,255));

	m_currentScreen->draw();

	if (m_overlayScreen != nullptr)
		m_overlayScreen->draw();

	m_engineManager->getWindow()->display();
}

void ScreenManager::changeScreen(Screen* p_newScreen)
{
	delete m_currentScreen;
	deleteOverlayScreen();

	m_currentScreen = p_newScreen;

	m_currentScreen->init();
}
