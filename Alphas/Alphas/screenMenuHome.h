#pragma once
#include "screen.h"

class ButtonText;

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

	ButtonText* m_buttonPlay;
	ButtonText* m_buttonOptions;
	ButtonText* m_buttonQuit;

	int	m_buttonFocused;
};

