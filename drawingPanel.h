#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <CustomLine.h>
#include <CustomShape.h>
#include <QFrame>
#include <QWidget>
#include <editingState.h>

class DrawingPanel : public QFrame
{
    Q_OBJECT
public:
    explicit DrawingPanel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    int outlineThickness;
    QColor outlineColor;
    QColor fillColor;
    Qt::PenStyle outlineStyle;

    int selectedShapeIndex;
    bool isShapeSelected = false;

    EditingState editingState = EditingState::Drawing;

    ShapeType currentShapeType;
    QVector<CustomShape> shapes;
    CustomShape currentShape;

    bool isDrawing = false; // Variable pour suivre si l'utilisateur est en train de dessiner
    bool isResizing = false; // Variable pour suivre si l'utilisateur est en train de redimensionner une forme
    bool isMoving = false;

    QPoint lastMovingAnchor;

public slots:
    void setThickness(int thickness);
    void setColor(const QColor& color);
    void setLineStyle(Qt::PenStyle style);
    void setShapeSelected(ShapeType shape);
    void fillShape();
    void eraseAll();
    void undo();

    void risizingMode();
    void movingMode();
private slots:
    //void on_spinbox1_valueChanged(int value);
    //void on_spinbox2_valueChanged(int value);
};

#endif // DRAWINGPANEL_H
