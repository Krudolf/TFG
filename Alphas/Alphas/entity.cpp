
#include "pch.h"
#include "entity.h"
#include "engineManager.h"
#include <iostream>

Entity::Entity(const char* p_path, Entities p_ent)
{
	m_engineManager = &EngineManager::p();
	m_spriteSheetRow = static_cast<int>(p_ent);

	/*
	TODO: Handle what happens if textureID is -1
	*/
	m_textureID = m_engineManager->loadTexture(p_path);
	m_spriteID = m_engineManager->createSprite(m_textureID, 0.5, true);
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
}

Entity::Entity(int p_textureID, Entities p_ent)
{
	m_engineManager = &EngineManager::p();
	m_spriteSheetRow = static_cast<int>(p_ent);

	m_textureID = p_textureID;
	m_spriteID = m_engineManager->createSprite(m_textureID, 0.5, true);
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
}


Entity::~Entity()
{
}


void Entity::update(float p_deltaTime)
{

}


void Entity::draw()
{
	m_engineManager->getWindow()->draw(*m_engineManager->getSprite(m_spriteID));
}