#pragma once
#include "screen.h"
#include "entities_enum.h"
#include "enemyType_enum.h"
#include "Point.h"

#include <vector>

class Camera;
class Entity;
class Player;
class Enemy;
class Potion;
class Projectile;
class SceneMap;
class HashGrid;
class Interface;
class WaveSystem;
class Tile;

class ScreenGame :
	public Screen
{
public:
	static std::vector<Player*>		m_playerVector;
	static std::vector<Enemy*>		m_enemyVector;
	static std::vector<Potion*>		m_potionVector;
	static std::vector<Projectile*>	m_projectileVector;
	static std::vector<Tile*>		m_tileCollisionVector;

	ScreenGame(Entities p_playerEntity);
	~ScreenGame();
	void deleteAndFree();

	virtual void init();
	virtual void update(double p_time, double p_deltaTime);
	virtual void draw();

	static bool getCooperativeMode();

	void fillHashGrid();

	void checkGameOver();
	void checkCollisionBetweenEnemys();

private:
	Camera*			m_camera;
	SceneMap*		m_sceneMap;
	HashGrid*		m_hashGrid;
	Interface*		m_interface;
	WaveSystem*		m_waveSystem;

	Entities		m_playerEntity;

	std::vector<Point>		m_spawnPointsVector;

	bool	m_gameOver;
	bool	m_gamePause;
};

