#pragma once
#include "screen.h"
#include <vector>

class Button;

class ScreenMenuHome :
	public Screen
{
public:
	ScreenMenuHome();
	~ScreenMenuHome();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*> m_buttonVector;

	Button* m_buttonPlay;
	Button* m_buttonOptions;
	Button* m_buttonQuit;

	int	m_buttonFocused;
};

