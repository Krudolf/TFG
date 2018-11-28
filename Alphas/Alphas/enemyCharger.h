#pragma once
#include "enemy.h"

class EnemyCharger :
	public Enemy
{
public:
	EnemyCharger(float p_posX, float p_posY, const char* p_path);
	~EnemyCharger();

	void moveBackwards() override;

	void atack();

	void updateAtack();
	
	void update(double p_time, double p_deltaTime) override;

private:
	bool	m_chargingAtack;
	bool	m_doingCharge;
	bool	m_chargePhase;
	bool	m_releasePhase;
	bool	m_lockDirection;

	float	m_chargeTime;
	float	m_releaseTime;
	float	m_endChargeTime;
	float	m_endReleaseTime;
};

