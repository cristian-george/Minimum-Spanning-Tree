#pragma once
#include <vector>
#include "Node.h"
#include "Edge.h"

class Graph
{
public:
	using T = size_t;
	using Edge = Edge<T>;
public:
	Graph() = default;

	void SetNodes(const std::vector<Node>& nodes);
	std::vector<Node> GetNodes() const;

	void SetEdges(const std::vector<Edge>& edges);
	std::vector<Edge> GetEdges() const;

	void SetAdjLists(const std::vector<std::vector<std::pair<size_t, T>>>& adjLists);
	std::vector<std::vector<std::pair<size_t, T>>> GetAdjLists() const;

	void AddNode(const QPointF& coordinates);
	void EraseNode(size_t number);

	void AddEdge(size_t firstNode, size_t secondNode, T cost = 0);
	void EraseEdge(size_t firstNode, size_t secondNode);

	void Clear();

public:
	std::vector<std::pair<size_t, T>>& operator[](size_t node);

public:
	std::vector<Edge> Prim(size_t start);
	std::vector<Edge> Kruskal(size_t start);
	std::vector<Edge> Boruvka(size_t start);

private:
	std::vector<Node> m_nodes;
	std::vector<Edge> m_edges;
	std::vector<std::vector<std::pair<size_t, T>>> m_adjLists;
};