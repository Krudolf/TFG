#pragma once
#include "screen.h"

class ButtonText;

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

	ButtonText* m_buttonSolo;
	ButtonText* m_buttonCooperativeAI;
	ButtonText* m_buttonCooperativeLocal;
	ButtonText* m_buttonBack;

	int	m_buttonFocused;
};

