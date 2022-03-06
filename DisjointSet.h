#pragma once
#include <vector>

template <class T>
class DisjointSet
{
public:
	DisjointSet(size_t dimension = 0);

	void MakeSet(const T& element);
	T FindSet(T element);
	void UnionSets(T element1, T element2);

private:
	std::vector<T> m_parent;
	std::vector<size_t> m_rank;
};