#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Point.h"

class EngineManager;

class Button
{
public:
	Button(std::string p_text, Point p_point);
	~Button();

	void setTextSize(int p_textSize) { m_textSize = p_textSize; };
	void setIsFocused(bool p_isFocused);
	bool getIsFocused() { return m_isFocused; };

	void draw();

private:
	EngineManager* m_engineManager;

	sf::RectangleShape	m_button;
	sf::Text			m_buttonText;

	bool		m_isFocused;

	std::string	m_text;

	int			m_textSize;
	
	float		m_buttonWidth;
	float		m_buttonHeight;
};

