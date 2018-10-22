#pragma once

#include <vector>
#include <array>
#include <SFML/Graphics.hpp>

class EngineManager;

class QuadTree
{
public:
	QuadTree(int p_level, sf::FloatRect p_bounds);
	~QuadTree();

	void clear();
	void split();
	int getIndex(sf::FloatRect p_rectangle);
	void insert(sf::Sprite* p_sprite);
	std::vector<sf::Sprite*> retrieve(std::vector<sf::Sprite*> p_returnObjects, sf::FloatRect p_rectangle);

	void debug();

private:
	EngineManager* m_engineManager;
	sf::RectangleShape* m_debug;

	const int MAX_OBJECTS = 50;
	const int MAX_LEVELS = 5;

	int m_level;
	std::vector<sf::Sprite*> m_objects;
	sf::FloatRect m_bounds;
	std::array<QuadTree*, 4> m_nodes;
};
