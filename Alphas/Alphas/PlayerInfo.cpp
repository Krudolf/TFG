#include "pch.h"
#include "playerInfo.h"
#include "player.h"
#include "color.h"
#include "fillBar.h"
#include "engineManager.h"

PlayerInfo::PlayerInfo(Player* p_owner, float p_posX, float p_posY, float p_sizeX, float p_sizeY)
{
	m_engineManager = &EngineManager::p();

	m_owner = p_owner;

	m_mainBox.setSize({ p_sizeX, p_sizeY });
	m_mainBox.setPosition(p_posX, p_posY);
	m_mainBox.setFillColor(sf::Color(170, 170, 170, 200));

	Color t_black = { 0, 0, 0, 255 };
	Color t_red = { 255, 0, 0, 255 };
	Color t_blue = { 0, 0, 255, 255 };

	float	t_offsetY = 10;
	float	t_barSizeX = p_sizeX - 50;
	float	t_barSizeY = 40;
	float	t_barPosX = p_posX + 25;
	float	t_barPosY = p_posY + t_offsetY;

	m_healthBar = new FillBar(t_barSizeX, t_barSizeY, t_barPosX, t_barPosY, t_black, t_red);
	m_manaBar = new FillBar(t_barSizeX, t_barSizeY, t_barPosX, t_barPosY + t_barSizeY + t_offsetY, t_black, t_blue);
}


PlayerInfo::~PlayerInfo()
{
	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_manaBar;
	m_manaBar = nullptr;
}

void PlayerInfo::update()
{
	m_healthBar->update(m_owner->getHealth() / m_owner->getMaxHealth());
	m_manaBar->update(m_owner->getMana() / m_owner->getMaxMana());
}

void PlayerInfo::draw()
{
	m_engineManager->draw(m_mainBox);
	m_healthBar->draw();
	m_manaBar->draw();
}
