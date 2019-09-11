#include "pch.h"
#include "tileSkewer.h"
#include "player.h"
#include "enemy.h"
#include "engineManager.h"


TileSkewer::TileSkewer(const char* p_urlTexture, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY, int p_gid) : Tile(p_urlTexture, p_textureLeft, p_textureTop, p_textureWidth, p_textureHeight, p_posX, p_posY, p_gid)
{
	m_tileType = TileTypes::SKEWER;
	m_makeDamage = false;
	m_damage = 10;

	m_elapsedTime = 0.f;

	m_column = (m_gid * p_textureWidth / p_textureLeft) - 1;
}


TileSkewer::~TileSkewer()
{
}

void TileSkewer::applyEffect(Entity * p_entity)
{
	if (p_entity->getEntity() == Entities::PLAYER_BLUE || p_entity->getEntity() == Entities::PLAYER_GREEN || p_entity->getEntity() == Entities::PLAYER_YELLOW) {
		if (m_makeDamage) {
			Player* t_player = dynamic_cast<Player*>(p_entity);
			t_player->receiveTrapDamage(m_damage);
		}
	}
	else if (p_entity->getEntity() == Entities::ENEMY || p_entity->getEntity() == Entities::ENEMY_BOSS) {
		if (m_makeDamage) {
			Enemy* t_enemy = dynamic_cast<Enemy*>(p_entity);
			t_enemy->receiveTrapDamage(m_damage);
		}
	}
}

void TileSkewer::update(double p_time, double p_deltaTime)
{
	m_elapsedTime += p_deltaTime;

	if (m_elapsedTime < 0.5)
		m_engineManager->setSpriteFrame(m_spriteID, m_column);
	else if (m_elapsedTime >= 0.5 && m_elapsedTime < 0.8)
		m_engineManager->setSpriteFrame(m_spriteID, m_column + 1);
	else if (m_elapsedTime >= 0.8 && m_elapsedTime < 1.f)
		m_engineManager->setSpriteFrame(m_spriteID, m_column + 2);
	else if (m_elapsedTime >= 1.f && m_elapsedTime < 1.5) {
		m_engineManager->setSpriteFrame(m_spriteID, m_column + 3);
		m_makeDamage = true;
	}

	if (m_elapsedTime >= 1.5) {
		m_elapsedTime = 0;
		m_makeDamage = false;
	}
}
