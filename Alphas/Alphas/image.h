#pragma once
#include "Point.h"
#include "entities_enum.h"

#include <SFML/Graphics.hpp>

class EngineManager;

class Image
{
public:
	Image(const char* p_path, Entities p_player, Point p_point);
	~Image();

	void changeFrame(int p_frame);

	void draw();

private:
	EngineManager*	m_engineManager;

	sf::Sprite	m_image;
};

