#include "pch.h"
#include "game.h"
#include "screenGame.h"

std::vector<Player*>		ScreenGame::m_playerVector;
std::vector<Enemy*>			ScreenGame::m_enemyVector;
std::vector<Potion*>		ScreenGame::m_potionVector;
std::vector<Projectile*>	ScreenGame::m_projectileVector;
std::vector<Tile*>			ScreenGame::m_tileCollisionVector;

int main()
{
	Game game;

	game.run();

	return 0;
}