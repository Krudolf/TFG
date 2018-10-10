
#include "pch.h"
#include "entity.h"
#include "engineManager.h"
#include <iostream>

Entity::Entity()
{
	m_engineManager = &EngineManager::p();

	/*
	TODO: Handle what happens if textureID is -1
	TODO: Pass the path as a variable
	*/
	m_textureID = m_engineManager->loadTexture("assets/spriteazul.png");

	m_spriteID = m_engineManager->createSprite(m_textureID, 0.5, true);
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