#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <QColor>
#include <QColorDialog>
#include <QFrame>
#include <QLabel>
#include <ShapeType.h>
#include <qwidget.h>

class ToolPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ToolPanel(QWidget *parent = nullptr);

private:
    QFrame* colorDisplay;
    QLabel* thicknessLabel;
    ShapeType currentShape;

signals:
    void colorSelected(const QColor& color);
    void thicknessChanged(int thickness);
    void lineStyleChanged(Qt::PenStyle style);
    void shapeSelected(ShapeType shape);

private slots:
    void handleThicknessChanged(int thickness);
    void chooseColor();
    void handleLineStyleChanged(bool dashed);
    void selectShape(int shapeId);

};

#endif // TOOLPANEL_H
