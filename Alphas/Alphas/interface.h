#pragma once

#include <SFML/Graphics.hpp>

class EngineManager;
class FillBar;
class Player;
class PlayerInfo;

class Interface
{
public:
	Interface(Player* p_player1, Player* p_player2);
	~Interface();

	void update();
	void draw();

private:
	EngineManager* m_engineManager;

	PlayerInfo* m_player1Info;
	PlayerInfo* m_player2Info;

	int m_width;
	int m_height;
};

