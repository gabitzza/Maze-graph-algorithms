#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tema2AG.h"
#include "Graph.h"
#include "qpainter.h"

class Tema2AG : public QMainWindow
{
    Q_OBJECT

public:
    Tema2AG(QWidget *parent = nullptr);
    ~Tema2AG();

private slots:
    void onGrafButtonClicked();
    void onRadioButtonGreenPathsClicked();
      
private:
    Ui::Tema2AGClass ui;
    Graph m_graph;
    bool m_drawGraf;
    bool m_paintGreen;
protected:
    virtual void paintEvent(QPaintEvent* e);
};
