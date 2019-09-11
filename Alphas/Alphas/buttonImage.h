#pragma once
#include "button.h"
#include "entities_enum.h"


class ButtonImage :
	public Button
{
public:
	ButtonImage(const char* p_path, Entities p_player, Point p_point);
	~ButtonImage();

	Entities getEntityImage() { return m_entityImage; };

	void draw();

private:
	sf::Sprite	m_buttonImage;

	Entities	m_entityImage;

	bool	m_selected;
};

