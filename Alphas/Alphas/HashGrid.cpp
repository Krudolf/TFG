#include "pch.h"
#include "hashGrid.h"
#include "entity.h"
#include <math.h>
#include "engineManager.h"


HashGrid::HashGrid()
{
}


HashGrid::~HashGrid()
{
	clear();
}


HashGrid& HashGrid::p()
{
	static HashGrid instance;
	return instance;
}

void HashGrid::init(int p_mapWidth, int p_mapHeight, int p_cellSize)
{
	m_engineManager = &EngineManager::p();

	m_mapWidth	= p_mapWidth;
	m_mapHeight = p_mapHeight;
	m_cellSize	= p_cellSize;
	m_columns	= m_mapWidth / m_cellSize;
	m_rows		= m_mapHeight / m_cellSize;
	m_cellWidth = m_mapWidth / m_cellSize;
}

void HashGrid::clear()
{
	m_bucket.clear();
}

void HashGrid::registerObject(Entity * p_entity)
{
	std::vector<int> t_cellsID = getIdForObject(p_entity);
	
	for (int t_cell : t_cellsID) {
		m_bucket[t_cell].push_back(p_entity);
	}
}

std::vector<int> HashGrid::getIdForObject(Entity * p_entity)
{
	std::vector<int> t_cellsID;

	Point t_min = { p_entity->getPositionX() - p_entity->getWidth() / 2, p_entity->getPositionY() - p_entity->getHeight() / 2 };
	Point t_max = { p_entity->getPositionX() + p_entity->getWidth() / 2, p_entity->getPositionY() + p_entity->getHeight() / 2 };

	//TopLeft
	addToBucket(t_min, t_cellsID);
	
	//TopRigth
	addToBucket({ t_max.x, t_min.y }, t_cellsID);
	
	//BottomRigth
	addToBucket(t_max, t_cellsID);
	
	//BottomLeft
	addToBucket({ t_min.x, t_max.y }, t_cellsID);
	
	return t_cellsID;
}

std::vector<int> HashGrid::getIdForObjectPosition(float p_posX, float p_posY, float p_radius)
{
	std::vector<int> t_cellsID;

	Point t_min = { p_posX - p_radius, p_posY - p_radius };
	Point t_max = { p_posX + p_radius, p_posY + p_radius };

	//TopLeft
	addToBucket(t_min, t_cellsID);

	//TopRigth
	addToBucket({ t_max.x, t_min.y }, t_cellsID);

	//BottomRigth
	addToBucket(t_max, t_cellsID);

	//BottomLeft
	addToBucket({ t_min.x, t_max.y }, t_cellsID);

	return t_cellsID;
}

void HashGrid::addToBucket(Point p_point, std::vector<int>& p_cellIdVector)
{
	int t_cellPosition = (int)(std::floor(p_point.x / m_cellSize) + std::floor(p_point.y / m_cellSize) * m_cellWidth);
	bool t_alreadyAdded = false;

	for (int i = 0; i < p_cellIdVector.size(); i++) {
		if (p_cellIdVector[i] == t_cellPosition)
			t_alreadyAdded = true;
	}

	if (!t_alreadyAdded)
		p_cellIdVector.push_back(t_cellPosition);
}

std::vector<Entity*> HashGrid::getNearby(Entity * p_entity)
{
	std::vector<Entity*>	t_nearbyObjects;
	std::vector<int>		t_bucketID = getIdForObject(p_entity);

	for (int t_cellID : t_bucketID) {
		t_nearbyObjects.insert(t_nearbyObjects.end(), m_bucket[t_cellID].begin(), m_bucket[t_cellID].end());
	}

	return t_nearbyObjects;
}

std::vector<Entity*> HashGrid::getNearbyByPosition(float p_posX, float p_posY, float p_radius)
{
	std::vector<Entity*>	t_nearbyObjects;
	std::vector<int>		t_bucketID = getIdForObjectPosition(p_posX, p_posY, p_radius);

	for (int t_cellID : t_bucketID) {
		t_nearbyObjects.insert(t_nearbyObjects.end(), m_bucket[t_cellID].begin(), m_bucket[t_cellID].end());
	}

	return t_nearbyObjects;
}

void HashGrid::debug()
{
	for (int i = 0; i < m_columns; i++) {
		for (int j = 0; j < m_rows; j++) {
			sf::RectangleShape t_bounding;
			t_bounding.setSize({ (float)m_cellSize, (float)m_cellSize });
			t_bounding.setPosition(m_cellSize * i, m_cellSize * j);
			t_bounding.setFillColor(sf::Color(0, 0, 0, 0));
			t_bounding.setOutlineColor(sf::Color::Yellow);
			t_bounding.setOutlineThickness(2);

			m_engineManager->draw(t_bounding);
		}
	}
}

