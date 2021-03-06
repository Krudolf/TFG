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

	m_engineManager->loadTexture("assets/background.png");
	m_backGroundID = m_engineManager->createSprite("assets/background.png", 1.f, false, 0, 0, 1280, 720, 0.f, 0.f);

	CenterTop = { m_width * 0.5f, m_height * 0.1f };

	LeftList1_3 = { m_width * 0.25f, m_height * 0.45f };
	LeftList2_3 = { m_width * 0.25f, m_height * 0.65f };
	LeftList3_3 = { m_width * 0.25f, m_height * 0.85f };
	
	RightList1_3 = { m_width * 0.75f, m_height * 0.45f };
	RightList2_3 = { m_width * 0.75f, m_height * 0.65f };
	RightList3_3 = { m_width * 0.75f, m_height * 0.85f };
	
	CenterList2_4 = { m_width * 0.5f, m_height * 0.4f };
	CenterList3_4 = { m_width * 0.5f, m_height * 0.6f };

	Center_left = { m_width * 0.25f, m_height * 0.35f };
	Center_right = { m_width * 0.75f, m_height * 0.35f };
	Center_right2 = { m_width * 0.75f, m_height * 0.35f };

	Down_Left1_3 = { m_width * 0.1f, m_height * 0.7f };
	Down_Left2_3 = { m_width * 0.25f, m_height * 0.7f };
	Down_Left3_3 = { m_width * 0.4f, m_height * 0.7f };

	Down_Right1_3 = { m_width * 0.6f, m_height * 0.7f };
	Down_Right2_3 = { m_width * 0.75f, m_height * 0.7f };
	Down_Right3_3 = { m_width * 0.9f, m_height * 0.7f };
	
	Down_right = { m_width * 0.25f, m_height * 0.9f };
	Down_right_up = { m_width * 0.75f, m_height * 0.9f };

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

void Screen::drawBackGround()
{
	m_engineManager->draw(m_engineManager->getSprite(m_backGroundID));
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
