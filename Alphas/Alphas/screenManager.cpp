#include "pch.h"
#include "screenManager.h"
#include "screen.h"

ScreenManager::ScreenManager()
{
	m_currentScreen = nullptr;
}


ScreenManager::~ScreenManager()
{
	if (m_currentScreen != nullptr) {
		delete m_currentScreen;
		m_currentScreen = nullptr;
	}
}

ScreenManager & ScreenManager::p()
{
	static ScreenManager instance;

	return instance;
}

void ScreenManager::init()
{
	m_currentScreen->init();
}

void ScreenManager::update(double p_time, double p_deltaTime)
{
	m_currentScreen->update(p_time, p_deltaTime);
}

void ScreenManager::draw()
{
	m_currentScreen->draw();
}

void ScreenManager::changeScreen(Screen* p_newScreen)
{
	delete m_currentScreen;

	m_currentScreen = p_newScreen;

	m_currentScreen->init();
}
