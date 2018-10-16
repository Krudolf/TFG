#include "pch.h"
#include "camera.h"
#include "engineManager.h"
#include "entity.h"

#include <iostream>

Camera::Camera()
{
	m_engineManager = &EngineManager::p();

	//sf::View((target),(size of the rectangle));
	m_engineManager->createCameraView(0, 0, 600, 480);
	m_engineManager->getWindow()->setView(*m_engineManager->getCameraView());
}


Camera::~Camera()
{

}

void Camera::update()
{
	//std::cout << m_target->getPosition().x << ", " << m_target->getPosition().y << std::endl;
	m_engineManager->getCameraView()->setCenter(m_target->getPositionX(), m_target->getPositionY());
	m_engineManager->getWindow()->setView(*m_engineManager->getCameraView());
}
