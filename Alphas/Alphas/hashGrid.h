#pragma once

#include "Point.h"
#include <map>
#include <vector>

class Entity;
class EngineManager;

class HashGrid
{
public:
	~HashGrid();
	static HashGrid& p();

	void init(int p_mapWidth, int p_mapHeight, int p_cellSize);
	void clear();

	void					registerObject(Entity* p_entity);
	std::vector<Entity*>	getNearby(Entity* p_entity);
	std::vector<Entity*>	getNearbyByPosition(float p_posX, float p_posY, float p_radius);
	std::vector<Entity*>	getScreenEntities();

	void debug();

private:
	HashGrid();

	std::vector<int>		getIdForObject(Entity* p_entity);
	std::vector<int>		getIdForObjectPosition(float p_posX, float p_posY, float p_radius);
	void					addToBucket(Point p_point, std::vector<int>& p_cellIdVector);
	void					addNeightbour(int p_row, int p_col);
	void					getScreenQuadrants();
	
	EngineManager* m_engineManager;

	std::map<int, std::vector<Entity*>>	m_bucket;
	std::vector<int>	m_screenQuadrants;

	int		m_mapWidth;
	int		m_mapHeight;
	int		m_cellSize;
	int		m_columns;
	int		m_rows;
	float	m_cellWidth;
	
};

/*
Code adapted from: 
	https://conkerjo.wordpress.com/2009/06/13/spatial-hashing-implementation-for-fast-2d-collisions/
*/