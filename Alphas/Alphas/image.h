#pragma once
#include "Point.h"
#include "entities_enum.h"
#include "stats_enum.h"

#include <SFML/Graphics.hpp>

class EngineManager;

class Image
{
public:
	Image(const char* p_path, Point p_point);
	Image(const char* p_path, Entities p_player, Point p_point);
	Image(const char* p_path, int p_row, Point p_point);
	//Constructor for create icons
	Image(Stats p_stats, float p_posX, float p_posY);
	~Image();

	void changeFrame(int p_frame);
	void changeFrameHability(int p_frame);

	void setPosition(Point p_pos) { m_image.setPosition(p_pos.x, p_pos.y); };
	void setScale(float p_x, float p_y) { m_image.setScale(p_x, p_y); };
	void setTextureRect(int p_width, int p_pos, bool p_center);

	int getWidth()	{ return m_width; };
	int getHeight() { return m_height; };

	void draw();

private:
	EngineManager*	m_engineManager;

	sf::Sprite	m_image;

	int	m_width;
	int	m_height;
};

