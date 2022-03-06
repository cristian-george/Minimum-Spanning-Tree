#pragma once

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include "ui_MST.h"
#include "Graph.h"

class MST : public QMainWindow
{
    Q_OBJECT

public:
    MST(QWidget *parent = Q_NULLPTR);

    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

    void DrawNode(const Node& node, Qt::GlobalColor color);
    void DrawEdge(const Graph::Edge& edge, Qt::GlobalColor color, size_t width);

    void ReadGraph(const std::string& fileName);

private slots:
    void on_pushButton_DrawGraph_clicked();
    void on_pushButton_ClearGraph_clicked();
    void on_pushButton_Prim_clicked();
    void on_pushButton_Kruskal_clicked();
    void on_pushButton_Boruvka_clicked();

private:
    Ui::MainWindow ui;
    Graph graph;
    std::vector<Graph::Edge> edges;
    int selectedNode;
};
