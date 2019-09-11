#pragma once
#include "screen.h"

class ButtonText;
class Text;

class ScreenPause :
	public Screen
{
public:
	ScreenPause();
	~ScreenPause();
	
	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*>	m_buttonVector;

	Text*		m_textPause;

	ButtonText* m_buttonContinue;
	ButtonText*	m_buttonExitGame;

	int	m_buttonFocused;
};

