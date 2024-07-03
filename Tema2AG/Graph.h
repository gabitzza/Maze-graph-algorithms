#pragma once
#include "Arch.h"
#include <QMouseEvent>
#include <queue>
class Graph
{
	std::vector<Node> m_nodes;
	std::vector<Node> m_nodes_labirint;
	std::vector<Arch> m_arches;
	std::vector<std::vector<int>>matrix;
	std::vector<Node>m_exit;
public:
	void ReadMatrix(const QString& fileName);
	std::vector<std::vector<int>> GetMatrix();
	void addNode(Node n);
	void addArch(Node firstNode, Node secondNode);
	void CreateGraf();
	Node findNode(int i, int j);
    std::vector<Node>& getNodes();
	void CreateArches(); //crearea grafului
	std::vector<Arch>& getArches();
	Node getStartNode();
	std::vector<Node>GetNodeLabirint();
	std::vector<Node> BFS(Node start);
	void ColorNodes(int value);
	void ExitNodes();
	Node FindNodeFromValue(int v)
	{
		for (auto node : m_nodes)
		{
			if (node.getValue() == v)
				return node;
		}
		return Node(-1);
	}
	
};
	
