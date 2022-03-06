#include "MST.h"
#include <QPainter>
#include <QPainterPath>
#include <fstream>
#include <QDebug>
#include <QMessageBox>

MST::MST(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	selectedNode = -1;
}

void MST::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPoint point = event->pos();

		const auto& nodes = graph.GetNodes();
		for (const auto& node : nodes)
		{
			qreal x = node.GetCoordinates().x();
			qreal y = node.GetCoordinates().y();

			if (abs(x - point.x()) < 2 * Node::radius && abs(y - point.y()) < 2 * Node::radius)
			{
				selectedNode = node.GetNumber();
				break;
			}
		}

		if (selectedNode != -1)
		{
			update();
			return;
		}
	}
}

void MST::paintEvent(QPaintEvent* event)
{
	const auto& edges = graph.GetEdges();
	for (const auto& edge : edges)
		DrawEdge(edge, Qt::black, 2);

	for (const auto& edge : MST::edges)
		DrawEdge(edge, Qt::blue, 4);

	const auto& nodes = graph.GetNodes();
	for (const auto& node : nodes)
		DrawNode(node, Qt::white);

	if (selectedNode != -1)
		DrawNode(nodes[selectedNode], Qt::green);
}

void MST::DrawNode(const Node& node, Qt::GlobalColor color)
{
	QPainter painter(this);

	qreal x = node.GetCoordinates().x();
	qreal y = node.GetCoordinates().y();

	QRect rect(x - Node::radius, y - Node::radius, 2 * Node::radius, 2 * Node::radius);

	painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(color));
	painter.drawEllipse(rect);

	painter.setFont(QFont("Times", 12, QFont::Bold));
	painter.drawText(rect, Qt::AlignCenter, QString::number(node.GetNumber() + 1));
}

void MST::DrawEdge(const Graph::Edge& edge, Qt::GlobalColor color, size_t width)
{
	QPen pen(color, width);

	QPainter painter(this);
	painter.setPen(pen);

	QPointF firstNode = edge.GetFirstNode().GetCoordinates();
	QPointF secondNode = edge.GetSecondNode().GetCoordinates();

	QLineF line(firstNode, secondNode);
	painter.drawLine(line);

	qreal mX = (firstNode.x() + secondNode.x()) / 2;
	qreal mY = (firstNode.y() + secondNode.y()) / 2;

	pen.setColor(Qt::black);
	painter.setPen(pen);
	painter.setFont(QFont("Times", 12, QFont::Bold));
	painter.drawText(QPointF(mX, mY), QString::number(edge.GetCost()));
}

void MST::ReadGraph(const std::string& fileName)
{
	std::ifstream fin(fileName);

	size_t numberOfNodes, numberOfEdges;
	fin >> numberOfNodes >> numberOfEdges;

	QPointF windowSize(1920, 1080);
	QPointF center(windowSize.x() / 2, windowSize.y() / 2);
	qreal angle = 2 * M_PI / numberOfNodes;

	for (size_t index = 0; index < numberOfNodes; ++index)
	{
		qreal x = center.x() - center.x() / 2 * cos(angle * index);
		qreal y = center.y() - center.y() / 2 * sin(angle * index);

		graph.AddNode(QPointF(x, y));
	}

	size_t firstNode, secondNode, cost;
	while (!fin.eof())
	{
		fin >> firstNode >> secondNode >> cost;
		graph.AddEdge(firstNode, secondNode, cost);
	}
}

void MST::on_pushButton_DrawGraph_clicked()
{
	ReadGraph("graph.txt");
	ui.pushButton_DrawGraph->setDisabled(true);
	update();
}

void MST::on_pushButton_ClearGraph_clicked()
{
	edges.clear();
	selectedNode = -1;
	update();
}

void MST::on_pushButton_Prim_clicked()
{
	if (selectedNode != -1)
	{
		edges = graph.Prim(selectedNode);
		update();
	}
}

void MST::on_pushButton_Kruskal_clicked()
{
	if (selectedNode != -1)
	{
		edges = graph.Kruskal(selectedNode);
		update();
	}
}

void MST::on_pushButton_Boruvka_clicked()
{
	if (selectedNode != -1)
	{
		edges = graph.Boruvka(selectedNode);
		update();
	}
}
