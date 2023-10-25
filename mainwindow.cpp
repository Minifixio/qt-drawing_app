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
    ui->colorDisplayFrame->setStyleSheet(QString("background-color: %1;").arg("black"));
}

void Main::on_shapeSelectEllipseBtn_clicked() {
    ui->drawingPanel->setShapeSelected(ShapeType::Ellipse);
}
void Main::on_shapeSelectRectangleBtn_clicked() {
    ui->drawingPanel->setShapeSelected(ShapeType::Rectangle);
}
void Main::on_shapeSelectTriangleBtn_clicked() {
    ui->drawingPanel->setShapeSelected(ShapeType::Triangle);
}
void Main::on_shapeSelectLineBtn_clicked() {
    ui->drawingPanel->setShapeSelected(ShapeType::Line);
}
void Main::on_lineStyleSolidRadioBtn_toggled(bool toggled) {
    if (toggled) {
        ui->drawingPanel->setLineStyle(Qt::SolidLine);
    }
}
void Main::on_lineStyleDashedRadioBtn_toggled(bool toggled) {
    if (toggled) {
        ui->drawingPanel->setLineStyle(Qt::DashLine);
    }
}
void Main::on_lineThicknessSlider_valueChanged(int v) {
    ui->drawingPanel->setThickness(v);
}
void Main::on_chooseColorBtn_clicked() {
    this->chooseColor();
}
void Main::on_eraseAllBtn_clicked() {
    ui->drawingPanel->eraseAll();
}
void Main::on_undoBtn_clicked() {
    ui->drawingPanel->undo();
}
void Main::on_fillColorBtn_clicked() {
    ui->drawingPanel->fillShape();
}
void Main::on_resizeBtn_clicked() {
    ui->drawingPanel->risizingMode();
}
void Main::on_moveBtn_clicked() {
    ui->drawingPanel->movingMode();
}

void Main::chooseColor()
{
    QColorDialog colorDialog;
    QColor selectedColor = colorDialog.getColor();
    if (selectedColor.isValid())
    {
        ui->drawingPanel->setColor(selectedColor);
        ui->colorDisplayFrame->setStyleSheet(QString("background-color: %1;").arg(selectedColor.name()));
    }
}

Main::~Main()
{
    delete ui;
}

