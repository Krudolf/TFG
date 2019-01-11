#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Point.h"

class EngineManager;

class Text
{
public:
	Text(const char* p_text);
	~Text();

	void centerOrigin();
	void setText(const char* p_text)	{ m_text.setString(p_text); };
	void setSize(int p_textSize)		{ m_text.setCharacterSize(p_textSize); };
	void setPosition(Point p_pos)		{ m_text.setPosition( p_pos.x, p_pos.y ); };
	
	void draw();

private:
	EngineManager*	m_engineManager;

	sf::Text		m_text;
};

