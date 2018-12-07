
#include "pch.h"
#include "entity.h"
#include "engineManager.h"
#include <iostream>

//Constructor for other type of entities
Entity::Entity(const char* p_path, Entities p_entity)
{
	m_engineManager = &EngineManager::p();
	m_entity = p_entity;
	m_spriteSheetRow = static_cast<int>(p_entity);

	/*
	TODO: Handle what happens if textureID is -1
	*/
	m_texturePath = p_path;
	m_engineManager->loadTexture(m_texturePath);
	m_spriteID = m_engineManager->createSprite(m_texturePath, 0.5, true);
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
}

//Constructor for Tiles
Entity::Entity(const char * p_path, int p_textureLeft, int p_textureTop, int p_textureWidth, int p_textureHeight, float p_posX, float p_posY)
{
	m_engineManager = &EngineManager::p();

	m_texturePath = p_path;
	m_engineManager->loadTexture(m_texturePath);
	m_spriteID = m_engineManager->createSprite(m_texturePath, 1, true, p_textureLeft, p_textureTop, p_textureWidth, p_textureHeight, p_posX, p_posY);
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