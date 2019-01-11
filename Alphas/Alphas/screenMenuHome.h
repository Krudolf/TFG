#pragma once
#include "screen.h"

class ButtonText;
class Text;

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

	Text*		m_textAlphas;

	ButtonText* m_buttonPlay;
	ButtonText* m_buttonOptions;
	ButtonText* m_buttonQuit;

	int	m_buttonFocused;
};

