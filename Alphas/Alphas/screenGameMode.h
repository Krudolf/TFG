#pragma once
#include "screen.h"
#include <vector>

class Button;

class ScreenGameMode :
	public Screen
{
public:
	ScreenGameMode();
	~ScreenGameMode();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*> m_buttonVector;

	Button* m_buttonSolo;
	Button* m_buttonCooperativeAI;
	Button* m_buttonCooperativeLocal;
	Button* m_buttonBack;

	int	m_buttonFocused;
};

