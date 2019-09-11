#pragma once
#include "screen.h"
#include "entities_enum.h"

class ButtonText;
class Text;

class ScreenGameOver :
	public Screen
{
public:
	ScreenGameOver();
	~ScreenGameOver();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*>	m_buttonVector;

	Text*	m_textGameOver;

	ButtonText* m_buttonRetry;
	ButtonText*	m_buttonGoMenu;

	int	m_buttonFocused;
};

