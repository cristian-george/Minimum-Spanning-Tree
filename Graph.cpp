#include "Graph.h"
#include <queue>
#include "DisjointSet.h"
#include <algorithm>

void Graph::SetNodes(const std::vector<Node>& nodes)
{
	m_nodes = nodes;
}

std::vector<Node> Graph::GetNodes() const
{
	return m_nodes;
}

void Graph::SetEdges(const std::vector<Edge>& edges)
{
	m_edges = edges;
}

std::vector<Graph::Edge> Graph::GetEdges() const
{
	return m_edges;
}

void Graph::SetAdjLists(const std::vector<std::vector<std::pair<size_t, Graph::T>>>& adjLists)
{
	m_adjLists = adjLists;
}

std::vector<std::vector<std::pair<size_t, Graph::T>>> Graph::GetAdjLists() const
{
	return m_adjLists;
}

void Graph::AddNode(const QPointF& coordinates)
{
	Node node(coordinates);
	size_t number = m_nodes.size();
	node.SetNumber(number);

	m_nodes.push_back(std::move(node));
	m_adjLists.resize(number + 1);
}

void Graph::EraseNode(size_t number)
{
	if (number < 0 or number >= m_nodes.size())
		return;

	auto it = m_nodes.begin();
	it += number;
	m_nodes.erase(it);
}

void Graph::AddEdge(size_t firstNode, size_t secondNode, T cost)
{
	Edge edge(m_nodes[firstNode], m_nodes[secondNode], cost);
	m_edges.push_back(std::move(edge));

	m_adjLists[firstNode].push_back(std::make_pair(secondNode, cost));
	m_adjLists[secondNode].push_back(std::make_pair(firstNode, cost));
}

void Graph::EraseEdge(size_t firstNode, size_t secondNode)
{
	for (auto it = m_edges.begin(); it != m_edges.end(); ++it)
		if (it->GetFirstNode().GetNumber() == firstNode and it->GetSecondNode().GetNumber() == secondNode)
		{
			m_edges.erase(it);
			break;
		}
}

void Graph::Clear()
{
	m_nodes.clear();
	m_edges.clear();
	m_adjLists.clear();
}

std::vector<std::pair<size_t, Graph::T>>& Graph::operator[](size_t node)
{
	return m_adjLists[node];
}

std::vector<Graph::Edge> Graph::Prim(size_t start)
{
	size_t numberOfNodes = m_nodes.size();
	std::vector<bool> visited(numberOfNodes, false);

	std::vector<Edge> primEdges;
	std::vector<size_t> costs(numberOfNodes, SIZE_MAX);
	std::vector<size_t> cameFrom(numberOfNodes, -1);

	costs[start] = 0;

	using Pair = std::pair<T, size_t>;
	std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

	pq.push(std::make_pair(costs[start], start));

	while (!pq.empty() && primEdges.size() < numberOfNodes - 1)
	{
		size_t currNode = pq.top().second;
		T currCost = pq.top().first;
		pq.pop();

		if (visited[currNode])
			continue;

		if (cameFrom[currNode] != -1)
			primEdges.push_back(Edge(m_nodes[currNode], m_nodes[cameFrom[currNode]], currCost));

		for (const auto& [node, cost] : m_adjLists[currNode])
		{
			if (!visited[node] && cost < costs[node])
			{
				cameFrom[node] = currNode;
				costs[node] = cost;
				pq.push(std::make_pair(cost, node));
			}
		}

		visited[currNode] = true;
	}

	return primEdges;
}

std::vector<Graph::Edge> Graph::Kruskal(size_t start)
{
	size_t numberOfNodes = m_nodes.size();
	std::vector<Edge> kruskalEdges;

	std::vector<Edge> edges = m_edges;
	std::sort(edges.begin(), edges.end(),
		[](const Edge& edge1, const Edge& edge2)
		{
			return edge1.GetCost() < edge2.GetCost();
		}
	);

	DisjointSet<size_t> disjointSet(numberOfNodes);

	for (const auto& edge : edges)
	{
		if (kruskalEdges.size() >= numberOfNodes - 1)
			break;

		size_t firstNode = edge.GetFirstNode().GetNumber();
		size_t secondNode = edge.GetSecondNode().GetNumber();

		if (disjointSet.FindSet(firstNode) != disjointSet.FindSet(secondNode))
		{
			kruskalEdges.push_back(edge);
			disjointSet.UnionSets(firstNode, secondNode);
		}
	}

	return kruskalEdges;
}

std::vector<Graph::Edge> Graph::Boruvka(size_t start)
{
	size_t numberOfNodes = m_nodes.size();
	size_t numberOfEdges = m_edges.size();
	size_t numberOfSets = numberOfNodes;

	std::vector<Edge> boruvkaEdges;

	DisjointSet<size_t> disjointSet(numberOfNodes);

	while (numberOfSets > 1)
	{
		std::vector<int> minimumEdges(numberOfNodes, -1);
		size_t edgeIndex = 0;

		for (const auto& edge : m_edges)
		{
			const Node& firstNode = edge.GetFirstNode();
			const Node& secondNode = edge.GetSecondNode();

			size_t firstSet = disjointSet.FindSet(firstNode.GetNumber());
			size_t secondSet = disjointSet.FindSet(secondNode.GetNumber());

			if (firstSet == secondSet)
			{
				++edgeIndex;
				continue;
			}
			if (minimumEdges[firstSet] == -1 or
				edge.GetCost() < m_edges[minimumEdges[firstSet]].GetCost())
				minimumEdges[firstSet] = edgeIndex;

			if (minimumEdges[secondSet] == -1 or
				edge.GetCost() < m_edges[minimumEdges[secondSet]].GetCost())
				minimumEdges[secondSet] = edgeIndex;

			++edgeIndex;
		}

		for (const auto& edgeIndex : minimumEdges)
			if (edgeIndex != -1)
			{
				size_t firstNode = m_edges[edgeIndex].GetFirstNode().GetNumber();
				size_t secondNode = m_edges[edgeIndex].GetSecondNode().GetNumber();

				size_t firstSet = disjointSet.FindSet(firstNode);
				size_t secondSet = disjointSet.FindSet(secondNode);

				if (firstSet == secondSet)
					continue;

				boruvkaEdges.push_back(Edge(m_nodes[firstNode], m_nodes[secondNode], m_edges[edgeIndex].GetCost()));

				disjointSet.UnionSets(firstSet, secondSet);
				--numberOfSets;
			}
	}

	return boruvkaEdges;
}
