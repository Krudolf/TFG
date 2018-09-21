#pragma once

#include <SFML/Graphics.hpp>
#include  "entity.h"

class Camera
{
public:
	Camera(sf::RenderWindow* p_window);
	~Camera();

	void update();
	void setTarget(Entity* p_target) { m_target = p_target; }

private:
	sf::RenderWindow*	m_window;
	sf::View*			m_view;
	Entity*				m_target;
};

