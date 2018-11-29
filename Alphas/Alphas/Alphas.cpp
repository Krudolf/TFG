#include "pch.h"
#include "game.h"
#include "stateGame.h"

std::vector<Entity*>	StateGame::m_entityVector;
std::vector<Player*>	StateGame::m_playerVector;
std::vector<Enemy*>		StateGame::m_enemyVector;
std::vector<Potion*>	StateGame::m_potionVector;
int main()
{
	Game game;

	game.run();

	return 0;
}