#pragma once
#define NODE_H
#include <QFile>
#include <QTextStream>
#include <QPainter>

class Node
{
    int m_value;
    QPoint m_coordinate;
    std::pair<int, int>m_position;
    int m_colorValue;

public:
    Node();
    Node(int val);
    void setValue(int value);
    QPoint getCoordinate();
    int getValue() const;
    void setPosition(int i, int j);
    void setCoordinate(QPoint p);
    std::pair<int, int> getPosition() const;   
    void setColor(int colorValue);
    int getColor() const;
};

