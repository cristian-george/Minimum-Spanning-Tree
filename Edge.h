#pragma once
#include "Node.h"

template <class T>
class Edge
{
public:
	Edge(T cost = 0);
	Edge(const Node& firstNode, const Node& secondNode, T cost = 0);

	void SetCost(T cost);
	T GetCost() const;

	void SetFirstNode(const Node& firstNode);
	const Node& GetFirstNode() const;

	void SetSecondNode(const Node& secondNode);
	const Node& GetSecondNode() const;

private:
	T m_cost;
	Node m_firstNode;
	Node m_secondNode;
};