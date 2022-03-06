#include "Edge.h"

template<class T>
inline Edge<T>::Edge(T cost) : m_cost(cost) {}

template<class T>
inline Edge<T>::Edge(const Node& firstNode, const Node& secondNode, T cost) :
	m_firstNode(firstNode), m_secondNode(secondNode), m_cost(cost) {}

template<class T>
inline void Edge<T>::SetCost(T cost)
{
	m_cost = cost;
}

template<class T>
inline T Edge<T>::GetCost() const
{
	return m_cost;
}

template<class T>
inline void Edge<T>::SetFirstNode(const Node& firstNode)
{
	m_firstNode = firstNode;
}

template<class T>
inline const Node& Edge<T>::GetFirstNode() const
{
	return m_firstNode;
}

template<class T>
inline void Edge<T>::SetSecondNode(const Node& secondNode)
{
	m_secondNode = secondNode;
}

template<class T>
inline const Node& Edge<T>::GetSecondNode() const
{
	return m_secondNode;
}

template Edge<size_t>;