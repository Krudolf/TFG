#pragma once

#include "Point.h"
#include <map>
#include <vector>

class Entity;

class HashGrid
{
public:
	~HashGrid();
	static HashGrid& p();

	void init(int p_mapWidth, int p_mapHeight, int p_cellSize);
	void clear();

	void					registerObject(Entity* p_entity);
	std::vector<Entity*>	getNearby(Entity* p_entity);

	void debug();

private:
	HashGrid();

	std::vector<int>		getIdForObject(Entity* p_entity);
	void					addToBucket(Point p_point, float p_width, std::vector<int>& p_cellIdVector);
	
	int		m_mapWidth;
	int		m_mapHeight;
	int		m_cellSize;
	int		m_columns;
	int		m_rows;
	
	std::map<int, std::vector<Entity*>>	m_bucket;
};

/*
Code adapted from: 
	https://conkerjo.wordpress.com/2009/06/13/spatial-hashing-implementation-for-fast-2d-collisions/
*/