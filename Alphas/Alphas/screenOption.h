#pragma once
#include "screen.h"

class ButtonText;
class Text;

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
	
	Text*		m_textAlphas;
	ButtonText* m_buttonBack;

	int	m_buttonFocused;
};

