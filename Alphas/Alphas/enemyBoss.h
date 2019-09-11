#pragma once
#include "enemy.h"
#include "enemyType_enum.h"

#include <vector>

class Projectile;

class EnemyBoss :
	public Enemy
{
public:
	EnemyBoss(float p_posX, float p_posY, const char* p_path, int p_waveNumber);
	~EnemyBoss();

	void selectAttack();
	void atack();

	void chargeAttack();
	void rangeAtack();
	void spawnMinion();
	void launchProjectile();
	void createEnemy(EnemyType p_type);

	void updateAtack();
	void updateRangeAttack();
	void updateChargeAttack();
	void draw() override;

private:
	std::vector<Projectile*>	m_projectilesVector;

	float	m_secondProjectileTime; //Time to launch second projectile
	float	m_rangeAttackCooldown;
	float	m_chargeAttackCooldown;
	float	m_spawnMinionCooldown;
	float	m_rangeAttackEndCooldown;
	float	m_chargeAttackEndCooldown;
	float	m_spawnMinionEndCooldown;
	
	float	m_chargeTime;
	float	m_releaseTime;
	float	m_endChargeTime;
	float	m_endReleaseTime;

	bool	m_attackSelected;
	bool	m_rangeAttackSelected;
	bool	m_chargeAttackSelected;

	bool	m_rangeAttackLaunched;
	bool	m_chargeAttackLaunched;

	bool    m_firstProjectileLaunched;
	bool	m_chargePhase;
	bool	m_releasePhase;
	bool	m_lockDirection;

	bool	m_rangeAttackInCooldown;
	bool	m_chargeAttackInCooldown;

	int		m_wave;

};

