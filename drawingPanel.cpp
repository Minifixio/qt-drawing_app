#include "drawingPanel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QtDebug>

DrawingPanel::DrawingPanel(QWidget *parent)
    : QFrame(parent), outlineThickness(1), outlineColor(Qt::black), fillColor(Qt::black), outlineStyle(Qt::SolidLine)
{
    isDrawing = false;
}

void DrawingPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Pour un rendu plus lisse

    for (const CustomShape &shape : shapes)
    {
        QPen pen(shape.outlineColor, shape.outlineThickness, shape.outlineStyle);
        painter.setPen(pen);

        if (shape.isFilled)
        {
            painter.setBrush(QBrush(shape.fillColor));
        }
        else
        {
            painter.setBrush(Qt::NoBrush);
        }

        switch (shape.shapeType)
        {
        case ShapeType::Rectangle:
            painter.drawRect(shape.rect);
            break;
        case ShapeType::Triangle:
            painter.drawPolygon(shape.polygon);
            break;
        case ShapeType::Ellipse:
            painter.drawEllipse(shape.rect);
            break;
        case ShapeType::Line:
            painter.setPen(pen);
            painter.drawLine(shape.line);
        default:
            break;
        }
    }

    painter.setBrush(Qt::NoBrush);

    // Dessin de la ligne en cours si l'utilisateur est en train de dessiner
    if (editingState == EditingState::Drawing && isDrawing)
    {
        QPen pen(outlineColor, outlineThickness, outlineStyle);
        painter.setPen(pen);

        switch (currentShapeType)
        {
        case ShapeType::Rectangle:
            painter.drawRect(currentShape.rect);
            break;
        case ShapeType::Triangle:
            painter.drawPolygon(currentShape.polygon);
            break;
        case ShapeType::Ellipse:
            painter.drawEllipse(currentShape.rect);
            break;
        case ShapeType::Line:
             painter.drawLine(currentShape.line);
            break;
        default:
            break;
        }
    }

    if ((editingState == EditingState::Risizing || editingState == EditingState::Moving) && isShapeSelected == true) {
        if (shapes.isEmpty() == false) {
            shapes[selectedShapeIndex].drawResizeHandle(painter);
        }
    }

}

void DrawingPanel::fillShape()
{
    if (!shapes.isEmpty())
    {
        shapes.last().isFilled = true;
        shapes.last().fillColor = fillColor;
        update();
    }
}

void DrawingPanel::mousePressEvent(QMouseEvent *event)
{

    if ((editingState == EditingState::Risizing || editingState == EditingState::Moving) && event->button() == Qt::LeftButton)
    {

        if (isShapeSelected && editingState == EditingState::Risizing) {
            bool isOnResizeHandle = shapes[selectedShapeIndex].selectResizeHandle(event->pos());

            if (isOnResizeHandle) {
                isResizing = true;
                return;
            }
        }

        isShapeSelected = false;

        // Vérifier si le clic est à l'intérieur d'une forme
        for (int i = shapes.size() - 1; i >= 0; --i)
        {
            const CustomShape &shape = shapes[i];

            if (shape.shapeType == ShapeType::Line && shape.isPointOnLine(event->pos()))
            {
                // La forme a été cliquée, la sélectionner
                isShapeSelected = true;
                selectedShapeIndex = i;

                // Redessiner pour montrer la sélection
                update();
            }

            if (shape.shapeType == ShapeType::Rectangle && shape.rect.contains(event->pos()))
            {
                // La forme a été cliquée, la sélectionner
                isShapeSelected = true;
                selectedShapeIndex = i;

                // Redessiner pour montrer la sélection
                update();
            }

            if (shape.shapeType == ShapeType::Ellipse && shape.isInsideEllipse(event->pos()))
            {
                // La forme a été cliquée, la sélectionner
                isShapeSelected = true;
                selectedShapeIndex = i;

                // Redessiner pour montrer la sélection
                update();
            }

            if (isShapeSelected) {
                if (editingState == EditingState::Moving) {
                    isMoving = true;
                    lastMovingAnchor = event->pos();
                    this->setCursor(Qt::ClosedHandCursor);
                }

                return;
            }
        }

        // Si le clic n'était pas dans une forme existante, désélectionner la forme
        isShapeSelected = false;
        update();
    }


    if (editingState == EditingState::Drawing && event->button() == Qt::LeftButton)
    {
        if (currentShapeType == Line)
        {
            // Initialiser la ligne en cours
            currentShape = CustomShape(QLine(event->pos(), event->pos()), Line, outlineThickness, outlineColor, fillColor, outlineStyle);
        }
        else if (currentShapeType == Rectangle)
        {
            // Initialiser le rectangle en cours
            currentShape = CustomShape(QRect(event->pos(), event->pos()), Rectangle, outlineThickness, outlineColor, fillColor, outlineStyle);
        }
        else if (currentShapeType == Triangle)
        {
            // Initialiser le triangle en cours
            currentShape = CustomShape(QPolygon(QVector<QPoint>() << event->pos()), Triangle, outlineThickness, outlineColor, fillColor, outlineStyle);;
        }
        else if (currentShapeType == Ellipse)
        {
            // Initialiser l'ellipse en cours
            currentShape = CustomShape(QRect(event->pos(), event->pos()), Ellipse, outlineThickness, outlineColor, fillColor, outlineStyle);
            currentShape.rect.setTopLeft(event->pos());
            currentShape.rect.setWidth(1); // Initialisez la largeur à 1
            currentShape.rect.setHeight(1);
        }

        isDrawing = true;
    }
}

void DrawingPanel::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing)
    {
        if (currentShapeType == Line)
        {
            currentShape.line.setP2(event->pos());
        }
        else if (currentShapeType == Rectangle)
        {
            currentShape.rect.setBottomRight(event->pos());
        }
        else if (currentShapeType == Triangle)
        {
            currentShape.polygon << event->pos();
        }
        else if (currentShapeType == Ellipse)
        {
            currentShape.rect.setBottomRight(event->pos());
        }
    }

    if (isResizing) {
        shapes[selectedShapeIndex].resize(event->pos());
    }

    if (isMoving) {
        shapes[selectedShapeIndex].move(lastMovingAnchor, event->pos());
        lastMovingAnchor = event->pos();
    }

    update(); // Forcer le rafraîchissement de l'affichage

}

void DrawingPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        shapes.append(currentShape);

        // Réinitialiser la forme en cours
        currentShape = CustomShape();

        isDrawing = false;

        update(); // Forcer le rafraîchissement de l'affichage
    }

    if (event->button() == Qt::LeftButton && isResizing)
    {
        isResizing = false;

        update(); // Forcer le rafraîchissement de l'affichage
    }

    if (event->button() == Qt::LeftButton && isMoving)
    {
        isMoving = false;
        this->setCursor(Qt::ArrowCursor);

        update(); // Forcer le rafraîchissement de l'affichage
    }
}

void DrawingPanel::risizingMode() {
    editingState = EditingState::Risizing;
}

void DrawingPanel::movingMode() {
    editingState = EditingState::Moving;
}

void DrawingPanel::setThickness(int thickness)
{
    outlineThickness = thickness;
    update();
}

void DrawingPanel::setColor(const QColor& color)
{
    outlineColor = color;
    fillColor = color;
    update();
}

void DrawingPanel::setLineStyle(Qt::PenStyle style)
{
    outlineStyle = style;
    update();
}

void DrawingPanel::setShapeSelected(ShapeType shapeType)
{
    currentShapeType = shapeType;
    editingState = EditingState::Drawing;
    update();
}
void DrawingPanel::eraseAll() {
    isShapeSelected = false;
    shapes.clear();
    update();
}
void DrawingPanel::undo() {
    if (!shapes.isEmpty()) {
        shapes.pop_back();
    }
    update();
}
