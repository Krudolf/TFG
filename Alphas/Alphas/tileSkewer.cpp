#include "pch.h"
#include "tileSkewer.h"
#include "player.h"
#include "enemy.h"


TileSkewer::TileSkewer(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid) : Tile(p_urlTexture, p_textureLeft, p_textureTop, p_textureWidth, p_textureHeight, p_posX, p_posY, p_gid)
{
	m_tileType = TileTypes::SKEWER;
	m_damage = 5;
}


TileSkewer::~TileSkewer()
{
}

void TileSkewer::applyEffect(Entity * p_entity)
{
	if (p_entity->getEntity() == Entities::PLAYER_BLUE || p_entity->getEntity() == Entities::PLAYER_GREEN || p_entity->getEntity() == Entities::PLAYER_YELLOW) {
		Player* t_player = dynamic_cast<Player*>(p_entity);
		t_player->receiveTrapDamage(m_damage);
	}
	else if (p_entity->getEntity() == Entities::ENEMY || p_entity->getEntity() == Entities::ENEMY_BOSS) {
		Enemy* t_enemy = dynamic_cast<Enemy*>(p_entity);
		t_enemy->receiveTrapDamage(m_damage);
	}
}
