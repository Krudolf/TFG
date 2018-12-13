#pragma once
#include "screen.h"
#include "entities_enum.h"

class ButtonText;

class ScreenGameOver :
	public Screen
{
public:
	ScreenGameOver(Entities p_playerEntity);
	~ScreenGameOver();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*>	m_buttonVector;

	ButtonText* m_buttonRetry;
	ButtonText*	m_buttonGoMenu;

	Entities	m_playerEntity;

	int	m_buttonFocused;
};

