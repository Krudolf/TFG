#pragma once

#include <vector>

class EngineManager;
class Camera;
class Entity;

class Game
{
public:
	static std::vector<Entity*> m_entityVector;
	static std::vector<Entity*> m_playerVector;

	Game();
	~Game();

	void run();
	void update(double p_time, float p_deltaTime);
	void draw();
	void deleteAndFree();

	void createPlayer();

private:
	EngineManager* m_engineManager;
	Camera* m_camera;

	float m_time;
	float m_dt;
	float m_currentTime;
	float m_newTime;
	float m_frameTime;
	int FPS;
};

