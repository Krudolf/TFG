#include "pch.h"
#include "playerInfo.h"
#include "player.h"
#include "color.h"
#include "fillBar.h"
#include "habilityInfo.h"
#include "statsInfo.h"
#include "engineManager.h"
#include "entities_enum.h"

PlayerInfo::PlayerInfo(Player* p_owner, float p_posX, float p_posY, float p_sizeX, float p_sizeY)
{
	m_engineManager = &EngineManager::p();

	m_owner = p_owner;

	/* MAIN BOX THAT CONTAIN THE REST OF THE INFORMATION */
	m_mainBox.setSize({ p_sizeX, p_sizeY });
	m_mainBox.setPosition(p_posX, p_posY);

	switch (p_owner->getEntity())
	{
		case Entities::PLAYER_BLUE:
			m_mainBox.setFillColor(sf::Color(0, 195, 255, 200));
			break;
		case Entities::PLAYER_GREEN:
			m_mainBox.setFillColor(sf::Color(0, 255, 100, 200));
			break;
		case Entities::PLAYER_YELLOW:
			m_mainBox.setFillColor(sf::Color(255, 255, 80, 200));
			break;
	}

	Color t_black = { 0, 0, 0, 255 };
	Color t_red = { 255, 0, 0, 255 };
	Color t_blue = { 0, 0, 255, 255 };

	/* HEALTH AND MANA BARS */
	float	t_offsetY	= 10;
	float	t_barSizeX	= p_sizeX - 50;
	float	t_barSizeY	= 40;
	float	t_barPosX	= p_posX + p_sizeX/2;
	float	t_barPosY	= p_posY + t_offsetY*3;
	float	t_barPosY2	= t_barPosY + t_barSizeY + t_offsetY;

	m_healthBar = new FillBar(t_barSizeX, t_barSizeY, t_barPosX, t_barPosY, t_black, t_red);
	m_manaBar = new FillBar(t_barSizeX, t_barSizeY, t_barPosX, t_barPosY2, t_black, t_blue);

	/* HABILITY INFORMATION */
	float	t_skillSize = 32.f;
	float	t_skillPosX = t_barPosX - (t_barSizeX / 2) + (t_skillSize / 2);
	float	t_skillPosY = t_barPosY2 + t_barSizeY + t_offsetY;
	m_hability1 = new HabilityInfo(Hability::SPIN_BLUE, t_skillPosX, t_skillPosY, t_skillSize);
	
	float	t_skillPosX2 = t_barPosX;
	m_hability2 = new HabilityInfo(Hability::SPIN_BLUE, t_skillPosX2, t_skillPosY, t_skillSize);
	
	float	t_skillPosX3 = t_barPosX + (t_barSizeX / 2) - (t_skillSize / 2);
	m_hability3 = new HabilityInfo(Hability::SPIN_BLUE, t_skillPosX3, t_skillPosY, t_skillSize);

	/*
		TODO:
		HACER QUE LOS ATAQUES FUNCIONEN BIEN CON SU COOLDOWN, NO AL TUNTUN COMO ESTÁ AHORA
	*/

	/* STATS INFORMATION */
	float	t_statPosX	= t_skillPosX;
	float	t_statPosX2	= t_skillPosX3 - t_skillSize - 5;
	float	t_statPosY	= t_skillPosY + t_skillSize + t_offsetY / 2;
	float	t_statPosY2	= t_statPosY + t_skillSize + t_offsetY / 2;

	m_damageInfo		= new StatsInfo(Stats::DAMAGE,		p_owner, t_statPosX, t_statPosY);
	m_armorInfo			= new StatsInfo(Stats::ARMOR,		p_owner, t_statPosX, t_statPosY2);
	m_attackSpeedInfo	= new StatsInfo(Stats::ATACK_SPEED, p_owner, t_statPosX2, t_statPosY);
	m_velocityInfo		= new StatsInfo(Stats::VELOCITY,	p_owner, t_statPosX2, t_statPosY2);
}


PlayerInfo::~PlayerInfo()
{
	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_manaBar;
	m_manaBar = nullptr;

	delete m_hability1;
	m_hability1 = nullptr;

	delete m_hability2;
	m_hability2 = nullptr;

	delete m_hability3;
	m_hability3 = nullptr;
	
	delete m_damageInfo;
	m_damageInfo = nullptr;

	delete m_armorInfo;
	m_armorInfo = nullptr;

	delete m_attackSpeedInfo;
	m_attackSpeedInfo = nullptr;

	delete m_velocityInfo;
	m_velocityInfo = nullptr;
}

void PlayerInfo::update()
{
	m_healthBar->update(m_owner->getHealth() / m_owner->getMaxHealth());
	m_manaBar->update(m_owner->getMana() / m_owner->getMaxMana());

	m_hability1->update(m_owner->getHability1ActivationTime(), m_owner->getHability1CooldownDuration(), m_owner->getHability1EnoughMana());
	m_hability2->update(m_owner->getHability2ActivationTime(), m_owner->getHability2CooldownDuration(), m_owner->getHability2EnoughMana());
	m_hability3->update(m_owner->getHability3ActivationTime(), m_owner->getHability3CooldownDuration(), m_owner->getHability3EnoughMana());

	m_damageInfo->update();
	m_armorInfo->update();
	m_attackSpeedInfo->update();
	m_velocityInfo->update();
}

void PlayerInfo::draw()
{
	m_engineManager->draw(m_mainBox);
	m_healthBar->draw();
	m_manaBar->draw();
	m_hability1->draw();
	m_hability2->draw();
	m_hability3->draw();
	m_damageInfo->draw();
	m_armorInfo->draw();
	m_attackSpeedInfo->draw();
	m_velocityInfo->draw();
}
