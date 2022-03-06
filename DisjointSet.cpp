#include "DisjointSet.h"

template<class T>
inline DisjointSet<T>::DisjointSet(size_t dimension) :
	m_parent(dimension), m_rank(dimension) 
{
	for (size_t index = 0; index < dimension; ++index)
		MakeSet(index);
}

template<class T>
inline void DisjointSet<T>::MakeSet(const T& element)
{
	m_parent[element] = element;
	m_rank[element] = 0;
}

template<class T>
inline void DisjointSet<T>::UnionSets(T element1, T element2)
{
	element1 = FindSet(element1);
	element2 = FindSet(element2);

	if (element1 != element2)
	{
		if (m_rank[element1] < m_rank[element2])
			std::swap(element1, element2);

		m_parent[element2] = element1;
		if (m_rank[element1] == m_rank[element2])
			++m_rank[element1];
	}
}

template<class T>
T DisjointSet<T>::FindSet(T element)
{
	if (element == m_parent[element])
		return element;

	return m_parent[element] = FindSet(m_parent[element]);
}

template DisjointSet<size_t>;