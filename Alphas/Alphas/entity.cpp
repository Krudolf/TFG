
#include "pch.h"
#include "entity.h"
#include "engineManager.h"
#include "hashGrid.h"
#include <iostream>

//Constructor for other type of entities
Entity::Entity(const char* p_path, Entities p_entity)
{
	m_engineManager = &EngineManager::p();
	m_hashGrid = &HashGrid::p();
	m_entity = p_entity;
	m_spriteSheetRow = static_cast<int>(p_entity);

	m_width	 = 128/2;
	m_height = 128/2;

	m_texturePath = p_path;
	m_engineManager->loadTexture(m_texturePath);
	if (p_entity == Entities::ENEMY_BOSS) {
		m_width	 = 128*2;
		m_height = 128*2;
		m_spriteID = m_engineManager->createSprite(m_texturePath, 1, true, 128 * 0, 128 * 5, 128 * 2, 128 * 2, 0, 0);
	}
	else if (p_entity == Entities::ENEMY_BOSS_BULLET) {
		m_spriteID = m_engineManager->createSprite(m_texturePath, 0.5, true, 128 * 2, 128 * 5, 128, 128, 0, 0);
	}
	else if (p_entity == Entities::BULLET_BLUE || p_entity == Entities::BULLET_GREEN || p_entity == Entities::BULLET_YELLOW || p_entity == Entities::ENEMY_BULLET) {
		m_spriteID = m_engineManager->createSprite(m_texturePath, 0.5, true);
		m_spriteSheetRow -= 10;
	}
	else {
		m_spriteID = m_engineManager->createSprite(m_texturePath, 0.5, true);
		m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
	}
}

//Constructor for Tiles
Entity::Entity(const char * p_path, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY)
{
	m_engineManager = &EngineManager::p();
	m_hashGrid = &HashGrid::p();

	m_entity = Entities::TILE;

	m_width = p_textureWidth;
	m_height = p_textureHeight;
	m_posX = p_posX;
	m_posY = p_posY;

	m_texturePath = p_path;
	m_engineManager->loadTexture(m_texturePath);
	m_spriteID = m_engineManager->createSprite(m_texturePath, 1, false, p_textureLeft, p_textureTop, p_textureWidth, p_textureHeight, p_posX, p_posY);
}

Entity::~Entity()
{
}

void Entity::update(){}
void Entity::update(double p_time, double p_deltaTime){}

void Entity::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));
}