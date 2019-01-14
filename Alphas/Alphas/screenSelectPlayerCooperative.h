#pragma once
#include "screen.h"

class ButtonText;
class ButtonImage;
class Image;

class ScreenSelectPlayerCooperative :
	public Screen
{
public:
	ScreenSelectPlayerCooperative();
	~ScreenSelectPlayerCooperative();

	void updateImage();

	void updatePlayer1();
	void updatePlayer2();

	void init();
	void update(double p_time, double p_deltaTime);
	void draw();

private:
	std::vector<Button*>	m_buttonVector1;
	std::vector<Image*>		m_imageVector1;

	std::vector<Button*>	m_buttonVector2;
	std::vector<Image*>		m_imageVector2;

	int				m_arrayEntities[3];

	ButtonImage*	m_buttonBlue1;
	ButtonImage*	m_buttonGreen1;
	ButtonImage*	m_buttonYellow1;
	ButtonImage*	m_buttonBlue2;
	ButtonImage*	m_buttonGreen2;
	ButtonImage*	m_buttonYellow2;

	ButtonText*		m_buttonPlay;
	ButtonText*		m_buttonBack;

	Image*			m_imageCharacters1;
	Image*			m_imageCharacters2;

	int	m_buttonFocused1;
	int	m_buttonFocused2;
	int m_playerSelected1;
	int m_playerSelected2;

	bool	m_joystickReleased;
};

