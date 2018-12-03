#pragma once
#include "screen.h"

#include <vector>

class Button;

class ScreenOption :
	public Screen
{
public:
	ScreenOption();
	~ScreenOption();
	
	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*> m_buttonVector;

	Button* m_buttonBack;

	int	m_buttonFocused;
};

