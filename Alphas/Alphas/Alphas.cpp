
#include "pch.h"
#include "game.h"
#include <iostream>

std::vector<Entity*> Game::m_entityVector;
std::vector<Entity*> Game::m_playerVector;
int main()
{
	Game game;

	game.run();

	return 0;
}