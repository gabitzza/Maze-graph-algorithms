#include "Graph.h"
#include <unordered_map>
#include<queue>
#include <vector>
void Graph::ReadMatrix(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Eroare: Nu s-a putut deschide fisierul.";
        return;
    }

    QTextStream in(&file);
    int size;
    in >> size;
    int contor = 0;
    matrix.clear(); 
    matrix.resize(size+2, std::vector<int>(size+2, 0));  
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
           in>> matrix[i][j];  
           Node n;
           n.setValue(contor);
           contor++;
           n.setPosition(i, j);
           n.setColor(matrix[i][j]);  
           m_nodes_labirint.push_back(n);
            
        }
    }

    for (int i = 0; i <= size; i++)
    {
        matrix[i][0] = 0;
        matrix[0][i] = 0;
        matrix[size + 1][i] = 0;
        matrix[i][size + 1] = 0;
    }
    file.close();
}

std::vector<std::vector<int>> Graph::GetMatrix() 
{
    return matrix;
}

void Graph::addNode(Node n)
{
   m_nodes.push_back(n);
}

void Graph::addArch(Node firstNode, Node secondNode)
{
    m_arches.push_back({ firstNode,secondNode });
}

void Graph::CreateGraf()
{
    int contor = 0;
    for (int i = 1; i < GetMatrix().size() - 1; i++)
    {
        for (int j = 1; j < GetMatrix()[i].size() - 1; j++)
        {
            Node newNode(contor);
            if (GetMatrix()[i][j] > 0)
            {
                newNode.setPosition(i, j);
                newNode.setColor(GetMatrix()[i][j]);
                contor++;
                addNode(newNode);  
            }
        }
    }
}

std::vector<Node>& Graph::getNodes()
{
    return m_nodes;
}


Node Graph::findNode(int i, int j)
{
    std::pair<int,int> poz = std::make_pair(i, j);
    for (Node x : m_nodes_labirint)
    {
        if (x.getPosition() == poz)
            return x;
    }
    return Node(-1);
}

void Graph::CreateArches()
{
    std::pair<int, int> coord;
    coord.first = 60;
    coord.second = 60;
    int contor = 0;

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            Node n;
            
            n.setPosition(i, j);
            if (matrix[i][j] == 0)
            {
               
                n.setColor(0);  
            }
            else if (matrix[i][j] == 1)
            {
                n.setValue(contor);
                contor++;
                QPoint p(coord.first, coord.second);
                n.setCoordinate(p);
                n.setColor(1);
                this->m_nodes.push_back(n);
            }
            else if (matrix[i][j] == 2)
            {
                n.setValue(contor);
                contor++;
                QPoint p(coord.first, coord.second);
                n.setCoordinate(p);
                n.setColor(2);
                this->m_nodes.push_back(n);
            }
            else if(matrix[i][j]==3)
            {
                n.setValue(contor);
                contor++;
                QPoint p(coord.first, coord.second);
                n.setCoordinate(p);
                n.setColor(3);  
  
                this->m_nodes.push_back(n);
            }

            this->m_nodes_labirint.push_back(n);
            coord.first += 40;
        }
        coord.second += 40;
        coord.first = 60;
    }

    for (auto node : getNodes())
    {
        for (auto node2 : getNodes())
        {
            if (node.getPosition() != node2.getPosition())
            {
                if (node.getCoordinate().y() == node2.getCoordinate().y() + 40 && node.getCoordinate().x() == node2.getCoordinate().x())
                {
                    addArch(node, node2);
                    addArch(node2, node);
                }
                if (node.getCoordinate().y() == node2.getCoordinate().y() && node.getCoordinate().x() == node2.getCoordinate().x() + 40)
                {
                    addArch(node, node2);
                    addArch(node2, node);
                }
            }
        }
    }
}
std::vector<Arch>& Graph::getArches()
{
    return m_arches;
}

Node Graph::getStartNode()
{
    for (auto n : m_nodes)
    {
        if (n.getColor() == 3)
            return n;
    }
    return -1;
}

std::vector<Node> Graph::GetNodeLabirint()
{
    return m_nodes_labirint;
}


std::vector<Node> Graph::BFS(Node start)
{
    std::vector<int> U;
    std::queue<int> V;
    std::vector<int> W;
    std::vector< int> predec;
    std::vector<std::vector<int>> iesiri; // fiecare iesire si cum se ajunge acolo de la nod de la start
    std::vector<int> lungimi;

    V.push(start.getValue());
    for (auto x : m_nodes)
    {
        if (start.getValue() != x.getValue())
            U.push_back(x.getValue());
        predec.push_back( -1 );
        lungimi.push_back( 0 );
    }
    while (!V.empty())
    {
        Node head = V.front();

        std::vector<int> vecini;
        for (auto a : m_arches)
        {
            if (a.getFirstNode().getValue() == head.getValue())
                vecini.push_back(a.getSecondNode().getValue());
        }
        for (auto vec : vecini)
        {
            auto it = std::find(U.begin(), U.end(), vec);
            if (it != U.end())
            {
                V.push(vec);
                U.erase(it);
                predec[vec] = head.getValue();
                lungimi[vec] = lungimi[head.getValue()] + 1;
                if (FindNodeFromValue(vec).getColor() == 2) //nod de iesire
                {
                    std::vector<int> road;
                    int aux = vec;
                    while (aux != start.getValue())
                    {
                        road.push_back(aux);
                        aux = predec[aux];
                    }
                    road.push_back(start.getValue());
                    iesiri.push_back(road);
                }
            }
        }

        V.pop();
        W.push_back(head.getValue());
    }
    std::vector<Node> verde;
    for (auto drum : iesiri)
    {
        for (auto road : drum)
        {
            Node n;
            if (FindNodeFromValue(road).getColor() == 1)
                n.setColor(9);
            else
                n.setColor(FindNodeFromValue(road).getColor());
            n.setValue(road);
            n.setCoordinate(FindNodeFromValue(road).getCoordinate());
            n.setPosition(FindNodeFromValue(road).getPosition().first, FindNodeFromValue(road).getPosition().second);
            bool ok = false;
            for (auto node : verde)
            {
                if (n.getValue() == node.getValue())
                {
                    ok = true;
                }
            }
            if (ok==false)
            {
                verde.push_back(n);
            }
            
        }
    }
    for (auto node : m_nodes)
    {
        bool ok = false;
        for (auto node2 : verde)
        {
            if (node2.getValue() == node.getValue())
            {
                ok = true;
            }
        }
        if (ok == false)
        {
            verde.push_back(node);
        }
    }
    return verde;
}

void Graph::ColorNodes(int value)
{
   
    for (auto node : m_nodes_labirint)
    {
        if (node.getValue() == value)
        {
            node.setColor(9);
            break;
        }
    }
}


void Graph::ExitNodes()
{
    for (auto n : m_nodes_labirint)
    {
        if (n.getColor() == 2)
            m_exit.push_back(n);
    }
}
