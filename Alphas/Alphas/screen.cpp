#include "pch.h"
#include "screen.h"
#include "engineManager.h"
#include "screenManager.h"


Screen::Screen()
{
	m_engineManager = &EngineManager::p();
	m_screenManager = &ScreenManager::p();

	m_width		= m_engineManager->getWidth();
	m_height	= m_engineManager->getHeight();

	CenterList1_3 = { m_width * 0.5f, m_height * 0.25f };
	CenterList2_3 = { m_width * 0.5f, m_height * 0.5f };
	CenterList3_3 = { m_width * 0.5f, m_height * 0.75f };

	CenterList1_4 = { m_width * 0.5f, m_height * 0.2f };
	CenterList2_4 = { m_width * 0.5f, m_height * 0.4f };
	CenterList3_4 = { m_width * 0.5f, m_height * 0.6f };
	CenterList4_4 = { m_width * 0.5f, m_height * 0.8f };

	Center_left = { m_width * 0.25f, m_height * 0.3f };

	Down_Left1_3 = { m_width * 0.1f, m_height * 0.8f };
	Down_Left2_3 = { m_width * 0.25f, m_height * 0.8f };
	Down_Left3_3 = { m_width * 0.4f, m_height * 0.8f };
	
	Down_right_up = { m_width * 0.8f, m_height * 0.75f };
	Down_right = { m_width * 0.8f, m_height * 0.9f };

	m_buttonFocused = 0;
}


Screen::~Screen()
{
}

Screen& Screen::p()
{
	static Screen instance;
	return instance;
}

void Screen::init()
{
}

void Screen::update(double p_time, double p_deltaTime)
{
}

void Screen::draw()
{
}
