#pragma once
#include "button.h"

class ButtonText :
	public Button
{
public:
	ButtonText(std::string p_text, Point p_point);
	~ButtonText();

	void setTextSize(int p_textSize) { m_textSize = p_textSize; };

	void draw();

private:
	sf::Text	m_buttonText;

	std::string	m_text;

	int			m_textSize;
};

