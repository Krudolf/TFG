#pragma once

class Screen;

class ScreenManager
{
public:
	~ScreenManager();
	static ScreenManager& p();

	void setCurrentScreen(Screen* p_newScreen) { m_currentScreen = p_newScreen; };

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();
	void changeScreen(Screen* p_newScreen);

protected:
	ScreenManager();
	Screen*	m_currentScreen;
};

