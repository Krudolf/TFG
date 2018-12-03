#include "pch.h"
#include "game.h"
#include "screenGame.h"

std::vector<Entity*>	ScreenGame::m_entityVector;
std::vector<Player*>	ScreenGame::m_playerVector;
std::vector<Enemy*>		ScreenGame::m_enemyVector;
std::vector<Potion*>	ScreenGame::m_potionVector;
int main()
{
	Game game;

	game.run();

	return 0;
}