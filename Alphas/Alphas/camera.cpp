#include "pch.h"
#include "camera.h"
#include "engineManager.h"
#include "entity.h"

#include <iostream>

Camera::Camera()
{
	m_engineManager = &EngineManager::p();

	//sf::View((target),(size of the rectangle));
	m_engineManager->createCameraView(0, 0, 1980, 1080);
	m_engineManager->useGameView();
}


Camera::~Camera()
{

}

void Camera::update()
{
	m_engineManager->setTargetGameView(m_target->getPositionX(), m_target->getPositionY());
}
