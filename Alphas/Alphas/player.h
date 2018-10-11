#pragma once
#include "entity.h"
#include <vector>

class Entity;
class Projectile;

class Player :
	public Entity
{
public:
	Player(float p_posX, float p_posY, float p_velocity, const char* p_path);
	~Player();
	
	void move();
	void rangeAtack();
	void launchProjectile(Direction p_dir);
	
	void updateBasicAtack();
	void update(float p_deltaTime);
	void draw() override;

private:
	double	m_deltaTime;
	float	m_velocity;
	
	bool	m_basicInCooldown;
	float	m_cooldownBasic;
	float	m_nextBasic;
	std::vector<Projectile*> m_basicProjectiles;
	const int m_maxProjectiles = 10;
};