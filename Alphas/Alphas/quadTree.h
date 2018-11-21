#pragma once

#include <vector>
#include <array>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class EngineManager;
class Entity;

class QuadTree
{
	enum Quadrant {
		NotFound = -1,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
	};

public:
	QuadTree(int p_level, sf::FloatRect p_bounds);
	~QuadTree();

	void clear();
	void insert(Entity* p_entity);
	void retrieve(std::vector<Entity*>& p_returnObjects, Entity* p_entity);

	void debug();

private:
	void split();
	Quadrant getIndex(Entity* p_entity);
	bool insertInChild(Entity* p_entity);
	bool hasChildren();


	EngineManager* m_engineManager;
	sf::RectangleShape* m_debug;

	const int MAX_OBJECTS = 50;
	const int MAX_LEVELS = 4;

	int m_level;
	sf::FloatRect m_bounds;

	std::vector<Entity*> m_objects;
	std::array<QuadTree*, 4> m_nodes;
};
