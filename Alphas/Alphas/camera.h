#pragma once

class EngineManager;
class Entity;

class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void setTarget(Entity* p_target) { m_target = p_target; }

private:
	EngineManager*	m_engineManager;
	Entity*			m_target;
};

