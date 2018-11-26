#pragma once

#include <vector>

class EngineManager;
class Camera;
class Entity;
class Player;
class Enemy;
class Potion;
class SceneMap;
class QuadTree;

class Game
{
public:
	static std::vector<Entity*> m_entityVector;
	static std::vector<Player*>	m_playerVector;
	static std::vector<Enemy*>	m_enemyVector;
	static std::vector<Potion*> m_potionVector;

	Game();
	~Game();

	void run();
	void update(double p_time, double p_deltaTime);
	void draw();
	void deleteAndFree();

	static bool getCooperativeMode();

	void checkCollisionBetweenEnemys();

	void createPlayer();

	void createEnemy(float p_posX, float p_posY);

private:

	EngineManager*	m_engineManager;
	Camera*			m_camera;
	SceneMap*		m_sceneMap;
	QuadTree*		m_quadTree;

	double m_time;
	double m_dt;
	double m_currentTime;
	double m_accumulator;
	float m_newTime;
	float m_frameTime;
	int FPS;
};

