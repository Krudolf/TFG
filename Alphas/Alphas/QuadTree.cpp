#include "pch.h"
#include "quadTree.h"
#include "engineManager.h"
#include <iostream>

QuadTree::QuadTree(int p_level, sf::FloatRect p_bounds)
{
	m_engineManager = &EngineManager::p();
	m_debug = new sf::RectangleShape();
	
	m_level = p_level;
	m_bounds = p_bounds;
	m_objects.clear();
}


QuadTree::~QuadTree()
{
	clear();

	delete m_debug;
}

void QuadTree::clear()
{
	//Clear the objects that are in that part of the tree
	m_objects.clear();

	//Clear all the nodes and its childs
	for (int i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i] != NULL) {
			m_nodes[i]->clear();
			m_nodes[i] = nullptr;
		}
	}
}

void QuadTree::split()
{
	float t_subWidth = (m_bounds.width / 2);
	float t_subHeight = (m_bounds.height / 2);
	float x = m_bounds.left;
	float y = m_bounds.top;

	m_nodes[0] = new QuadTree(m_level + 1, sf::FloatRect(x + t_subWidth, y, t_subWidth, t_subHeight));
	m_nodes[1] = new QuadTree(m_level + 1, sf::FloatRect(x, y, t_subWidth, t_subHeight));
	m_nodes[2] = new QuadTree(m_level + 1, sf::FloatRect(x, y + t_subHeight, t_subWidth, t_subHeight));
	m_nodes[3] = new QuadTree(m_level + 1, sf::FloatRect(x + t_subWidth, y + t_subHeight, t_subWidth, t_subHeight));
}

int QuadTree::getIndex(sf::FloatRect p_rectangle)
{
	int t_index = -1;
	double t_verticalMidpoint = m_bounds.left + (m_bounds.width / 2);
	double t_horizontalMidpoint = m_bounds.top + (m_bounds.height / 2);

	//Object fit within the top quadrants
	bool t_topQuadrant = (p_rectangle.top < t_horizontalMidpoint && ((p_rectangle.top + p_rectangle.height) < t_horizontalMidpoint));
	//Object fit within the bottom quadrants
	bool t_bottomQuadrant = (p_rectangle.top > t_horizontalMidpoint);

	//Object fit within the left quadrants
	if (p_rectangle.left < t_verticalMidpoint && ((p_rectangle.left + p_rectangle.width) < t_verticalMidpoint)) {
		if (t_topQuadrant)
			t_index = 1;
		else if (t_bottomQuadrant)
			t_index = 2;
	}
	//Object fit within the right quadrants
	else if (p_rectangle.left > t_verticalMidpoint) {
		if (t_topQuadrant)
			t_index = 0;
		else if (t_bottomQuadrant)
			t_index = 3;
	}

	return t_index;
}

void QuadTree::insert(sf::Sprite* p_sprite)
{
	if (m_nodes[0] != NULL) {
		int t_index = getIndex(p_sprite->getGlobalBounds());

		if (t_index != -1) {
			m_nodes[t_index]->insert(p_sprite);

			return;
		}
	}

	m_objects.push_back(p_sprite);

	if (m_objects.size() > MAX_OBJECTS && m_level < MAX_LEVELS) {
		if (m_nodes[0] == NULL)
			split();

		int i = 0;
		while (i < m_objects.size()) {
			int t_index = getIndex(m_objects[i]->getGlobalBounds());
			if (t_index != -1) {
				m_nodes[t_index]->insert(m_objects[i]);
				m_objects.erase(m_objects.begin() + i);
			}
			else
				i++;
		}
	}
}

std::vector<sf::Sprite*> QuadTree::retrieve(std::vector<sf::Sprite*> p_returnObjects, sf::FloatRect p_rectangle)
{
	int t_index = getIndex(p_rectangle);
	if (t_index != -1 && m_nodes[0] != NULL)
		m_nodes[t_index]->retrieve(p_returnObjects, p_rectangle);

	p_returnObjects.insert(p_returnObjects.end(), m_objects.begin(), m_objects.end());

	return p_returnObjects;
}

void QuadTree::debug()
{
	m_debug->setSize(sf::Vector2f(m_bounds.width, m_bounds.height));
	m_debug->setFillColor(sf::Color::Transparent);
	m_debug->setOutlineColor(sf::Color::Yellow);
	m_debug->setOutlineThickness(2);
	m_debug->setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
			
	m_engineManager->getWindow()->draw(*m_debug);
	for (int i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i] != NULL) {
			
			m_nodes[i]->debug();
		}
	}
}
