
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
	m_texturePath = p_path;
	m_engineManager->loadTexture(m_texturePath);
	m_spriteID = m_engineManager->createSprite(p_path, 0.5, true);
	m_engineManager->setSpriteFrame(m_spriteID, m_spriteSheetRow, 0);
}

Entity::~Entity()
{
}


void Entity::update(){}
void Entity::update(float p_deltaTime){}


void Entity::draw()
{
	m_engineManager->draw(m_engineManager->getSprite(m_spriteID));
}