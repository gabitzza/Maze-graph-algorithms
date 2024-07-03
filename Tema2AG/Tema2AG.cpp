#include "Tema2AG.h"

Tema2AG::Tema2AG(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.checkBox, &QCheckBox::clicked, this, &Tema2AG::onGrafButtonClicked);
    connect(ui.checkBox_2, &QCheckBox::clicked, this, &Tema2AG::onRadioButtonGreenPathsClicked);
    m_graph.ReadMatrix("matrix.txt");
    m_drawGraf = false;
    m_paintGreen = false;
  //  m_graph.CreateGraf();
    m_graph.CreateArches();
    update();
}

Tema2AG::~Tema2AG()
{
}

void Tema2AG::onGrafButtonClicked()
{
    if (ui.checkBox->isChecked() == true)
        m_drawGraf = true;
    else
        m_drawGraf = false;
    update();
}

void Tema2AG::onRadioButtonGreenPathsClicked()
{
    if (ui.checkBox_2->isChecked() == true)
    {
        m_paintGreen = true;
    }
    else
        m_paintGreen = false;
}

void Tema2AG::paintEvent(QPaintEvent* e)
{
	if (m_paintGreen == false)
	{
		if (m_drawGraf == false)
		{
			QPainter painter(this);
			std::vector<std::vector<int>>mat = m_graph.GetMatrix();
			for (int i = 1; i < mat.size() - 1; i++)
			{
				for (int j = 1; j < mat[i].size() - 1; j++)
				{
					if (m_graph.findNode(i, j).getColor() == 0)
					{
						painter.setBrush(Qt::black);
						painter.drawRect(j * 40, i * 40, 40, 40);
					}
					else if (m_graph.findNode(i, j).getColor() == 2)
					{
						painter.setBrush(Qt::red);
						painter.drawRect(j * 40, i * 40, 40, 40);
					}
					else if (m_graph.findNode(i, j).getColor() == 3)
					{
						painter.setBrush(Qt::blue);
						painter.drawRect(j * 40, i * 40, 40, 40);
					}
					else
					{
						painter.setBrush(Qt::white);
						painter.drawRect(j * 40, i * 40, 40, 40);
					}
				}
			}
			update();
		}
		else
		{
			QPainter p(this);
			for (auto x : m_graph.getNodes())
			{
				std::pair<int, int> aux = x.getPosition();
				int col = x.getColor();
				if (col == 2)
					p.setBrush(Qt::red);
				else if (col == 3)
					p.setBrush(Qt::blue);
				else
					p.setBrush(Qt::white);
				QRect r(x.getCoordinate().x() - 10, x.getCoordinate().y() - 10, 20, 20);
				p.drawEllipse(r);
				update();
			}

			for (auto a : m_graph.getArches())
			{
				if (a.getFirstNode().getPosition() != a.getSecondNode().getPosition())
				{
					if (a.getFirstNode().getCoordinate().y() == a.getSecondNode().getCoordinate().y() + 40 && a.getFirstNode().getCoordinate().x() == a.getSecondNode().getCoordinate().x())
					{
						p.setPen(QPen(Qt::black));
						int x1 = a.getFirstNode().getCoordinate().x();
						int x2 = a.getSecondNode().getCoordinate().x();
						int y1 = a.getFirstNode().getCoordinate().y() - 10;
						int y2 = a.getSecondNode().getCoordinate().y() + 10;
						QPoint x(x1, y1);
						QPoint y(x2, y2);
						p.drawLine(x, y);
						update();

					}
					if (a.getFirstNode().getCoordinate().y() == a.getSecondNode().getCoordinate().y() && a.getFirstNode().getCoordinate().x() == a.getSecondNode().getCoordinate().x() + 40)
					{
						p.setPen(QPen(Qt::black));
						int x1 = a.getFirstNode().getCoordinate().x() - 10;
						int x2 = a.getSecondNode().getCoordinate().x() + 10;
						int y1 = a.getFirstNode().getCoordinate().y();
						int y2 = a.getSecondNode().getCoordinate().y();
						QPoint x(x1, y1);
						QPoint y(x2, y2);
						p.drawLine(x, y);
						update();

					}
				}
			}
		}
	}
	else
	{
		if (m_drawGraf == false)
		{
			QPainter p(this);
			std::vector<Node> verde = m_graph.BFS(m_graph.getStartNode());

			for (auto n : verde)
			{
				int i = n.getPosition().first;
				int j = n.getPosition().second;
				if (n.getColor() == 0)
				{
					p.setBrush(Qt::black);
				}
				else if (n.getColor() == 2)
				{
					p.setBrush(Qt::red);
				}
				else if (n.getColor() == 3)
				{
					p.setBrush(Qt::blue);
				}
				else if (n.getColor() == 9)
				{
					p.setBrush(Qt::green);
				}
				else
					p.setBrush(Qt::white);

				p.drawRect(j * 40, i * 40, 40, 40);
				update();
			}
		}
		else
		{
			QPainter p(this);
			std::vector<Node> verde = m_graph.BFS(m_graph.getStartNode());
			for (auto x : verde)
			{
				std::pair<int, int> aux = x.getPosition();
				int col = x.getColor();
				if (col == 0)
					p.setBrush(Qt::black);
				else if (col == 2)
					p.setBrush(Qt::red);
				else if (col == 3)
					p.setBrush(Qt::blue);
				else if (col == 9)
					p.setBrush(Qt::green);
				else
					p.setBrush(Qt::white);
				QRect r(x.getCoordinate().x() - 10, x.getCoordinate().y() - 10, 20, 20);
				p.drawEllipse(r);
				update();
			}

			for (auto a : m_graph.getArches())
			{
				if (a.getFirstNode().getPosition() != a.getSecondNode().getPosition())
				{
					if (a.getFirstNode().getCoordinate().y() == a.getSecondNode().getCoordinate().y() + 40 && a.getFirstNode().getCoordinate().x() == a.getSecondNode().getCoordinate().x())
					{
						p.setPen(QPen(Qt::black));
						int x1 = a.getFirstNode().getCoordinate().x();
						int x2 = a.getSecondNode().getCoordinate().x();
						int y1 = a.getFirstNode().getCoordinate().y() - 10;
						int y2 = a.getSecondNode().getCoordinate().y() + 10;
						QPoint x(x1, y1);
						QPoint y(x2, y2);
						p.drawLine(x, y);
						update();
					}
					if (a.getFirstNode().getCoordinate().y() == a.getSecondNode().getCoordinate().y() && a.getFirstNode().getCoordinate().x() == a.getSecondNode().getCoordinate().x() + 40)
					{
						p.setPen(QPen(Qt::black));
						int x1 = a.getFirstNode().getCoordinate().x() - 10;
						int x2 = a.getSecondNode().getCoordinate().x() + 10;
						int y1 = a.getFirstNode().getCoordinate().y();
						int y2 = a.getSecondNode().getCoordinate().y();
						QPoint x(x1, y1);
						QPoint y(x2, y2);
						p.drawLine(x, y);
						update();
					}
				}

			}

		}

	}
}