#include "pch.h"
#include "quadTree.h"
#include "engineManager.h"
#include "entity.h"
#include <iostream>
#include <functional>

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
	delete m_debug;
}

void QuadTree::clear()
{
	//Clear the objects that are in that part of the tree
	m_objects.clear();

	if (!hasChildren())
		return;

	//Clear all the nodes and its childs
	for (int i = 0; i < m_nodes.size(); i++) {
			m_nodes[i]->clear();
			delete m_nodes[i];
			m_nodes[i] = nullptr;
	}
}

void QuadTree::split()
{
	int t_width = (int)(m_bounds.width / 2);
	int t_height =(int)(m_bounds.height / 2);
	int x = (int)m_bounds.left;
	int y = (int)m_bounds.top;

	m_nodes[TopLeft]		= new QuadTree(m_level + 1, sf::FloatRect(x, y, t_width, t_height));
	m_nodes[TopRight]		= new QuadTree(m_level + 1, sf::FloatRect(x + t_width, y, t_width, t_height));
	m_nodes[BottomLeft]		= new QuadTree(m_level + 1, sf::FloatRect(x, y + t_height, t_width, t_height));
	m_nodes[BottomRight]	= new QuadTree(m_level + 1, sf::FloatRect(x + t_width, y + t_height, t_width, t_height));
}

QuadTree::Quadrant QuadTree::getIndex(Entity* p_entity)
{
	sf::FloatRect t_rectangle = m_engineManager->getSprite(p_entity->getSpriteID())->getGlobalBounds();
	//std::cout << t_rectangle.left << ", " << t_rectangle.top << ", " << t_rectangle.width << ", " << t_rectangle.height << std::endl;

	double t_verticalMidpoint = m_bounds.left + (m_bounds.width / 2);
	double t_horizontalMidpoint = m_bounds.top + (m_bounds.height / 2);

	// Can the object "completely" fit within this quadrant?
	bool top = ((t_rectangle.top + t_rectangle.height) < t_horizontalMidpoint);
	bool bottom = (t_rectangle.top > t_horizontalMidpoint);
	bool left = ((t_rectangle.left + t_rectangle.width) < t_verticalMidpoint);
	bool right = (t_rectangle.left > t_verticalMidpoint);

	if (top && left)
		return TopLeft;

	if (top && right)
		return TopRight;

	if (bottom && left)
		return BottomLeft;

	if (bottom && right)
		return BottomRight;

	return NotFound;
}

void QuadTree::insert(Entity* p_entity)
{
	if (hasChildren() && insertInChild(p_entity))
		return;

	m_objects.push_back(p_entity);

	// This node is already split, and we can't move any objects down.
	if (hasChildren())
		return;

	// Can't split this node, so no point checking number of objects.
	if (m_level == MAX_LEVELS)
		return;

	// Don't need to split this node yet.
	if (m_objects.size() < MAX_OBJECTS)
		return;

	split();

	int i = 0;
	while (i < m_objects.size()) {
		Entity* t_entity = m_objects[i];
		auto t_index = getIndex(p_entity);
			if (t_index != -1) {
				m_nodes[t_index]->insert(t_entity);
				m_objects.erase(m_objects.begin() + i);
			}
			else
				i++;
	}

	/*m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
			std::bind(&QuadTree::insertInChild, this, std::placeholders::_1)),
		m_objects.end());*/
}

void QuadTree::retrieve(std::vector<Entity*>& p_returnObjects, Entity* p_entity)
{
	if (hasChildren()) {
		auto t_index = getIndex(p_entity);
		//std::cout << static_cast<Quadrant>(t_index) << std::endl;

		if (t_index != NotFound) {
			m_nodes[t_index]->retrieve(p_returnObjects, p_entity);
		}
	}
	
	std::copy(m_objects.begin(), m_objects.end(), std::back_inserter(p_returnObjects));
	//p_returnObjects.insert(p_returnObjects.end(), m_objects.begin(), m_objects.end());
}

bool QuadTree::insertInChild(Entity * p_entity)
{
	auto t_index = getIndex(p_entity);

	if (t_index == NotFound)
		return false;

	m_nodes[0]->insert(p_entity);

	return true;
}

bool QuadTree::hasChildren()
{
	return (m_nodes[0] != nullptr);
}

void QuadTree::debug()
{
	m_debug->setSize(sf::Vector2f(m_bounds.width, m_bounds.height));
	m_debug->setFillColor(sf::Color::Transparent);

	m_debug->setOutlineThickness(2);
	m_debug->setPosition(sf::Vector2f(m_bounds.left, m_bounds.top));
			
	m_engineManager->getWindow()->draw(*m_debug);
	for (int i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i] != nullptr) {
			
			m_nodes[i]->debug();
		}
	}
}
