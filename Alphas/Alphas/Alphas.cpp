
#include "pch.h"
#include "game.h"
#include <iostream>

std::vector<Entity*> Game::m_entityVector;
std::vector<Player*>	Game::m_playerVector;
std::vector<Enemy*>		Game::m_enemyVector;
std::vector<Potion*>	Game::m_potionVector;
int main()
{
	Game game;

	game.run();

	return 0;
}