#pragma once
#include <QPoint>

class Node
{
public:
	Node(size_t number = 0);
	Node(const QPointF& coordinates);
	Node(size_t number, const QPointF& coordinates);

	void SetNumber(size_t number);
	size_t GetNumber() const;

	void SetCoordinates(const QPointF& coordinates);
	QPointF GetCoordinates() const;

public:
	static size_t radius;

private:
	size_t m_number;
	QPointF m_coordinates;
};

