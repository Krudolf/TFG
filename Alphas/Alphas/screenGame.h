#pragma once
#include "screen.h"
#include "entities_enum.h"

#include <vector>

class Camera;
class Entity;
class Player;
class Enemy;
class Potion;
class SceneMap;
class QuadTree;

class ScreenGame :
	public Screen
{
public:
	static std::vector<Entity*> m_entityVector;
	static std::vector<Player*>	m_playerVector;
	static std::vector<Enemy*>	m_enemyVector;
	static std::vector<Potion*> m_potionVector;

	ScreenGame(Entities p_playerEntity);
	~ScreenGame();
	void deleteAndFree();

	virtual void init();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

	static bool getCooperativeMode();

	void checkCollisionBetweenEnemys();
	void createEnemyWarrior(float p_posX, float p_posY);
	void createEnemyCharger(float p_posX, float p_posY);
	void createEnemyRanger(float p_posX, float p_posY);

private:
	Camera*			m_camera;
	SceneMap*		m_sceneMap;
	QuadTree*		m_quadTree;

};

