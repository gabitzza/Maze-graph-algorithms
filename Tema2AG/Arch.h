#pragma once
#include "Node.h"
class Arch
{
    Node m_firstNode, m_secondNode;
public:
    Arch();
    Arch(Node firstNode, Node secondNode);
     Node& getFirstNode();
     Node& getSecondNode();
};

