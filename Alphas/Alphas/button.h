#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Point.h"
#include "color.h"

class EngineManager;

class Button
{
public:
	Button(Point p_point);
	virtual ~Button();

	void setIsFocused(bool p_isFocused);
	bool getIsFocused() { return m_isFocused; };

	void setIsBlocked(bool p_isBlocked);
	bool getIsBlocked() { return m_isBlocked; };

	virtual void draw() = 0;

protected:
	EngineManager* m_engineManager;

	sf::RectangleShape	m_button;

	Color	m_shoftGrey;
	Color	m_darkGrey;
	Color	m_shoftBlue;
	Color	m_darkBlue;

	bool		m_isFocused;
	bool		m_isBlocked;

	float		m_posX;
	float		m_posY;
	float		m_buttonWidth;
	float		m_buttonHeight;
	
};

