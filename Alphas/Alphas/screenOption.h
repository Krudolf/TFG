#pragma once
#include "screen.h"

class ButtonText;
class Text;
class Image;

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
	
	Image*	m_keyboardImage;
	Image*	m_controllerImage;

	Text*		m_textAlphas;
	
	ButtonText* m_buttonPlay;
	ButtonText* m_buttonOptions;
	ButtonText* m_buttonQuit;

	int	m_buttonFocused;
};

