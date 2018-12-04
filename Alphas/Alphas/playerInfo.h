#pragma once
#include <SFML/Graphics.hpp>

class EngineManager;
class Player;
class FillBar;

class PlayerInfo
{
public:
	PlayerInfo(Player* p_owner, float p_posX, float p_posY, float p_sizeX, float p_sizeY);
	~PlayerInfo();

	void update();
	void draw();

private:
	EngineManager*	m_engineManager;

	Player*	m_owner;

	sf::RectangleShape	m_mainBox;

	FillBar*	m_healthBar;
	FillBar*	m_manaBar;
};

