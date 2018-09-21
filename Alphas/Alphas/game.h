#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "player.h"
#include "camera.h"

class Game
{
public:
	sf::RenderWindow* m_window;
	static std::vector<Entity*> m_entityVector;
	static std::vector<Entity*> m_playerVector;

	Game();
	~Game();

	void run();
	void update();
	void draw();
	void deleteAndFree();

	void createPlayer();

private:
	Camera* m_camera;

	double m_time;
	double m_dt;
	double m_currentTime;
	double m_newTime;
	double m_frameTime;
	int FPS;

	sf::Clock m_masterClock;

};

