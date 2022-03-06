#include "Node.h"

size_t Node::radius = 20;

Node::Node(size_t number) : 
	m_number(number) {}

Node::Node(const QPointF& coordinates) : 
	m_coordinates(coordinates)
{
	m_number = 0;
}

Node::Node(size_t number, const QPointF& coordinates) :
	m_number(number), m_coordinates(coordinates) {}

void Node::SetNumber(size_t number)
{
	m_number = number;
}

size_t Node::GetNumber() const
{
	return m_number;
}

void Node::SetCoordinates(const QPointF& coordinates)
{
	m_coordinates = coordinates;
}

QPointF Node::GetCoordinates() const
{
	return m_coordinates;
}