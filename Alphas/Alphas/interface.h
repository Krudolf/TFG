#pragma once

#include <SFML/Graphics.hpp>

class EngineManager;
class FillBar;
class Player;
class PlayerInfo;
class WaveSystem;

class Interface
{
public:
	Interface(Player* p_player1, Player* p_player2, WaveSystem* p_waveSystem);
	~Interface();

	void update();
	void draw();

private:
	EngineManager* m_engineManager;

	PlayerInfo* m_player1Info;
	PlayerInfo* m_player2Info;
	WaveSystem*	m_waveSystem;

	int m_width;
	int m_height;

	sf::Text	m_waveInfo;
	std::string	m_waveText;
};

