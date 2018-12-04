#pragma once
#include "screen.h"

class ButtonText;
class ButtonImage;
class Image;

class ScreenSelectPlayerSolo :
	public Screen
{
public:
	ScreenSelectPlayerSolo();
	~ScreenSelectPlayerSolo();

	void updateImage();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*> m_buttonVector;
	std::vector<Image*> m_imageVector;

	int				m_arrayEntities[3];

	ButtonImage*	m_buttonBlue;
	ButtonImage*	m_buttonGreen;
	ButtonImage*	m_buttonYellow;
	ButtonText*		m_buttonPlay;
	ButtonText*		m_buttonBack;
	Image*			m_imageCharacters;

	int	m_buttonFocused;
	int m_playerSelected;
};

