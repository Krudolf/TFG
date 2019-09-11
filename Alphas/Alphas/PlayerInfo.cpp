#include "pch.h"
#include "playerInfo.h"
#include "player.h"
#include "color.h"
#include "fillBar.h"
#include "habilityInfo.h"
#include "statsInfo.h"
#include "engineManager.h"
#include "entities_enum.h"
#include "image.h"
#include "text.h"

PlayerInfo::PlayerInfo(Player* p_owner, float p_posX, float p_posY)
{
	m_engineManager = &EngineManager::p();

	m_owner = p_owner;

	/* MAIN BOX THAT CONTAIN THE REST OF THE INFORMATION */
	m_mainBox = new Image("assets/playerBox.png", { p_posX, p_posY });

	float t_sizeX = m_mainBox->getWidth();
	float t_sizeY = m_mainBox->getHeight();

	Point t_pos = { p_posX, (p_posY - (t_sizeY / 2)) };
	m_mainBox->setPosition(t_pos);

	Color t_black	= { 0, 0, 0, 255 };
	Color t_red		= { 255, 0, 0, 255 };
	Color t_blue	= { 0, 0, 255, 255 };
	Color t_yellow	= { 255, 255, 0, 255 };

	/* HEALTH AND MANA BARS */
	float	t_offsetY	= 10;
	float	t_barSizeX	= t_sizeX * 0.275;
	float	t_barSizeY	= 32;
	float	t_barPosX	= t_pos.x + t_sizeX * -0.275;
	float	t_barPosX2	= t_pos.x + t_sizeX * 0.275;
	float	t_barPosY	= t_pos.y + t_sizeY * -0.1;
	float	t_barPosY2	= t_pos.y + t_sizeY * 0.3;

	m_healthBar		= new FillBar(t_barSizeX, t_barSizeY, t_barPosX, t_barPosY, t_black, t_red);
	m_manaBar		= new FillBar(t_barSizeX, t_barSizeY, t_barPosX2, t_barPosY, t_black, t_blue);
	m_experienceBar = new FillBar(t_barSizeX, t_barSizeY, t_barPosX, t_barPosY2, t_black, t_yellow);

	m_levelText = new Text("Lvl: X");
	m_levelText->setPosition({ t_barPosX, t_barPosY2-5 });
	m_levelText->setSize(20);
	m_levelText->centerOrigin();

	/* HABILITY INFORMATION */
	float	t_skillSize = 32.f;
	float	t_skillPosX = t_pos.x + t_sizeX * -0.075;
	float	t_skillPosY = t_barPosY;
	m_hability1 = new HabilityInfo(t_skillPosX, t_skillPosY, t_skillSize, p_owner->getEntity(), 0);
	
	float	t_skillPosX2 = t_pos.x;
	m_hability2 = new HabilityInfo(t_skillPosX2, t_skillPosY, t_skillSize, p_owner->getEntity(), 1);
	
	float	t_skillPosX3 = t_pos.x + t_sizeX * 0.075;
	m_hability3 = new HabilityInfo(t_skillPosX3, t_skillPosY, t_skillSize, p_owner->getEntity(), 2);

	/* STATS INFORMATION */
	float	t_statPosX	= t_pos.x + t_sizeX * -0.1;
	float	t_statPosX2 = t_pos.x + t_sizeX * 0.033;
	float	t_statPosX3 = t_pos.x + t_sizeX * 0.166;
	float	t_statPosX4	= t_pos.x + t_sizeX * 0.299;
	float	t_statPosY	= t_pos.y + t_sizeY * 0.3;

	m_damageInfo		= new StatsInfo(Stats::DAMAGE,		p_owner, t_statPosX, t_statPosY);
	m_armorInfo			= new StatsInfo(Stats::ARMOR,		p_owner, t_statPosX2, t_statPosY);
	m_attackSpeedInfo	= new StatsInfo(Stats::ATACK_SPEED, p_owner, t_statPosX3, t_statPosY);
	m_velocityInfo		= new StatsInfo(Stats::VELOCITY,	p_owner, t_statPosX4, t_statPosY);
}


PlayerInfo::~PlayerInfo()
{
	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_manaBar;
	m_manaBar = nullptr;

	delete m_experienceBar;
	m_experienceBar = nullptr;

	delete m_levelText;
	m_levelText = nullptr;

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

	delete m_mainBox;
	m_mainBox = nullptr;
}

void PlayerInfo::update()
{
	m_healthBar->update(m_owner->getHealth() / m_owner->getMaxHealth());
	m_manaBar->update(m_owner->getMana() / m_owner->getMaxMana());
	m_experienceBar->update(m_owner->getCurrentExp() / m_owner->getTopExp());

	m_levelText->setText("Lvl: " + std::to_string(m_owner->getLevel()));

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
	m_mainBox->draw();
	m_healthBar->draw();
	m_manaBar->draw();
	m_experienceBar->draw();
	m_levelText->draw();
	m_hability1->draw();
	m_hability2->draw();
	m_hability3->draw();
	m_damageInfo->draw();
	m_armorInfo->draw();
	m_attackSpeedInfo->draw();
	m_velocityInfo->draw();
}
