#pragma once
#include "color.h"
#include <SFML/Graphics.hpp>

class EngineManager;

class FillBar
{
public:
	FillBar(float p_sizeX, float p_sizeY, float p_posX, float p_posY, Color p_color1, Color p_color2);
	~FillBar();

	void update(float p_size);
	void update(float p_size, float p_posX, float p_posY);
	void draw();

private:
	EngineManager* m_engineManager;

	sf::RectangleShape	m_background;
	sf::RectangleShape	m_upperground;

	float m_offset;
	float m_sizeX;
};

