#pragma once

#include <vector>
#include <array>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class EngineManager;
class Entity;

class QuadTree
{
public:
	QuadTree(int p_level, sf::FloatRect p_bounds);
	~QuadTree();

	void clear();
	void split();
	int getIndex(Entity* p_entity);
	void insert(Entity* p_entity);
	std::vector<Entity*> retrieve(std::vector<Entity*> p_returnObjects, Entity* p_entity);

	void debug();

private:
	EngineManager* m_engineManager;
	sf::RectangleShape* m_debug;

	const int MAX_OBJECTS = 100;
	const int MAX_LEVELS = 5;

	int m_level;
	std::vector<Entity*> m_objects;
	sf::FloatRect m_bounds;
	std::array<QuadTree*, 4> m_nodes;

	bool m_playerInQuadrant;
};
