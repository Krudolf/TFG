#pragma once
#include "Point.h"

class EngineManager;
class ScreenManager;

class Screen
{
public:
	virtual ~Screen();
	static Screen& p();

	virtual void init();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

protected:
	Screen();

	EngineManager* m_engineManager;
	ScreenManager* m_screenManager;

	int	m_width;
	int	m_height;

	int		m_buttonFocused;

	Point CenterList1_3;
	Point CenterList2_3;
	Point CenterList3_3;

	Point CenterList1_4;
	Point CenterList2_4;
	Point CenterList3_4;
	Point CenterList4_4;

	Point Down_right;
};
