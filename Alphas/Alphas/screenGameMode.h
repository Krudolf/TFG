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
	std::vector<Button*> m_buttonVectorStatic;
	std::vector<Button*> m_buttonVector;

	ButtonText* m_buttonPlay;
	ButtonText* m_buttonOptions;
	ButtonText* m_buttonQuit;

	ButtonText* m_buttonSolo;
	ButtonText* m_buttonCooperative;

	int	m_buttonFocused;
};

