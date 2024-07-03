#include "Node.h"

Node::Node()
{
    m_value = -1;
    m_position.first = -1;
    m_position.second = -1;
    m_colorValue = -1;
}

Node::Node(int val)
{
    this->m_value = val;
    m_position.first = -1;
    m_position.second = -1;
    m_colorValue = -1;
}

void Node::setValue(int value)
{
    this->m_value = value;
}

QPoint Node::getCoordinate()
{
    return m_coordinate;
}

int Node::getValue() const
{
    return m_value;
}

void Node::setPosition(int i, int j)
{
    m_position.first = i;
    m_position.second = j;
}

void Node::setCoordinate(QPoint p)
{
    this->m_coordinate = p;
}

std::pair<int, int> Node::getPosition() const
{
    return  std::pair<int, int>(m_position.first, m_position.second);
}

void Node::setColor(int colorVal)
{
    m_colorValue = colorVal;
}

int Node::getColor() const
{
    return m_colorValue;
}