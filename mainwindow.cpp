#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingPanel.h"
#include <QVBoxLayout>
#include <ToolPanel.h>
#include "toolPanel.h"

Main::Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main)
{
    ui->setupUi(this);

    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto mainLayout = new QHBoxLayout(centralWidget);

    toolPanel = new ToolPanel(centralWidget);

    auto drawingPanel = new DrawingPanel(*toolPanel, centralWidget);

    mainLayout->addWidget(drawingPanel);
    mainLayout->addWidget(toolPanel);

    centralWidget->setLayout(mainLayout);

}

Main::~Main()
{
    delete ui;
}

