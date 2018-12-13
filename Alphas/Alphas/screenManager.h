#pragma once

class EngineManager;
class Screen;

class ScreenManager
{
public:
	~ScreenManager();
	static ScreenManager& p();

	void setCurrentScreen(Screen* p_newScreen) { m_currentScreen = p_newScreen; };
	void setOverlayScreen(Screen* p_newScreen) { m_overlayScreen = p_newScreen; };

	void deleteOverlayScreen();

	bool overlayOpened();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();
	void changeScreen(Screen* p_newScreen);

protected:
	ScreenManager();

	EngineManager*	m_engineManager;
	
	Screen*	m_currentScreen;
	Screen*	m_overlayScreen;

};

