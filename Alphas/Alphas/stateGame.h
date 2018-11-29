#pragma once
#include "state.h"

#include <vector>

class Camera;
class Entity;
class Player;
class Enemy;
class Potion;
class SceneMap;
class QuadTree;

class StateGame :
	public State
{
public:
	static std::vector<Entity*> m_entityVector;
	static std::vector<Player*>	m_playerVector;
	static std::vector<Enemy*>	m_enemyVector;
	static std::vector<Potion*> m_potionVector;

	~StateGame();
	void deleteAndFree();
	static StateGame& p();

	virtual void init();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

	static bool getCooperativeMode();

	void checkCollisionBetweenEnemys();
	void createPlayer();
	void createEnemyWarrior(float p_posX, float p_posY);
	void createEnemyCharger(float p_posX, float p_posY);
	void createEnemyRanger(float p_posX, float p_posY);

private:
	StateGame();
	
	Camera*			m_camera;
	SceneMap*		m_sceneMap;
	QuadTree*		m_quadTree;

};

