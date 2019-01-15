#pragma once
#include "Point.h"
#include <vector>

class EngineManager;
class ScreenManager;
class Button;
class Image;

class Screen
{
public:
	virtual ~Screen();
	static Screen& p();

	void drawBackGround();

	virtual void init();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

protected:
	Screen();

	EngineManager* m_engineManager;
	ScreenManager* m_screenManager;

	float	m_width;
	float	m_height;

	int		m_backGroundID;
	int		m_buttonFocused;

	Point CenterTop;

	Point LeftList1_3;
	Point LeftList2_3;
	Point LeftList3_3;

	Point RightList1_3;
	Point RightList2_3;
	Point RightList3_3;

	Point CenterList2_4;
	Point CenterList3_4;

	Point Center_left;
	Point Center_right;
	Point Center_right2;

	Point Down_Left1_3;
	Point Down_Left2_3;
	Point Down_Left3_3;
	
	Point Down_Right1_3;
	Point Down_Right2_3;
	Point Down_Right3_3;

	Point Down_right;
	Point Down_right_up;
};

