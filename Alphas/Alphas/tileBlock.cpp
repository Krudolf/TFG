#include "pch.h"
#include "tileBlock.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"


TileBlock::TileBlock(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid) : Tile(p_urlTexture, p_textureLeft, p_textureTop, p_textureWidth, p_textureHeight, p_posX, p_posY, p_gid)
{
	m_tileType = TileTypes::BLOCK;
}


TileBlock::~TileBlock()
{
}

void TileBlock::applyEffect(Entity* p_entity)
{
	if (p_entity->getEntity() == Entities::PLAYER_BLUE || p_entity->getEntity() == Entities::PLAYER_GREEN || p_entity->getEntity() == Entities::PLAYER_YELLOW) {
		Player* t_player = dynamic_cast<Player*>(p_entity);
		t_player->moveBackwards();
	}
	else if (p_entity->getEntity() == Entities::ENEMY || p_entity->getEntity() == Entities::ENEMY_BOSS) {
		Enemy* t_enemy = dynamic_cast<Enemy*>(p_entity);
		t_enemy->moveBackwards();
	}
	else if (p_entity->getEntity() == Entities::BULLET_BLUE || p_entity->getEntity() == Entities::BULLET_GREEN || p_entity->getEntity() == Entities::BULLET_YELLOW || p_entity->getEntity() == Entities::ENEMY_BULLET || p_entity->getEntity() == Entities::ENEMY_BOSS_BULLET) {
		Projectile* t_projectile = dynamic_cast<Projectile*>(p_entity);
		t_projectile->setReadyToDelete(true);
	}
}
