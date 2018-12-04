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

	CenterList1_3.x = m_width * 0.5;
	CenterList1_3.y = m_height * 0.25;
	CenterList2_3.x = m_width * 0.5;
	CenterList2_3.y = m_height * 0.5;
	CenterList3_3.x = m_width * 0.5;
	CenterList3_3.y = m_height * 0.75;

	CenterList1_4.x = m_width * 0.5;
	CenterList1_4.y = m_height * 0.2;
	CenterList2_4.x = m_width * 0.5;
	CenterList2_4.y = m_height * 0.4;
	CenterList3_4.x = m_width * 0.5;
	CenterList3_4.y = m_height * 0.6;
	CenterList4_4.x = m_width * 0.5;
	CenterList4_4.y = m_height * 0.8;

	Center_left.x = m_width * 0.25;
	Center_left.y = m_height * 0.3;

	Down_Left1_3.x = m_width * 0.1;
	Down_Left1_3.y = m_height * 0.8;
	Down_Left2_3.x = m_width * 0.25;
	Down_Left2_3.y = m_height * 0.8;
	Down_Left3_3.x = m_width * 0.4;
	Down_Left3_3.y = m_height * 0.8;
	
	Down_right_up.x = m_width * 0.8;
	Down_right_up.y = m_height * 0.75;
	Down_right.x = m_width * 0.8;
	Down_right.y = m_height * 0.9;

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
