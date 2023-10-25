#include "customShape.h"

#include <QLine>
#include <QtDebug>
#include <QColor>

// Constructeur par défaut
CustomShape::CustomShape() {}

// Constructeur pour une ligne
CustomShape::CustomShape(const QLine &r, ShapeType st, int ot, const QColor &oc, const QColor &fc, Qt::PenStyle os)
    : line(r), shapeType(st), outlineThickness(ot), outlineColor(oc), fillColor(fc), outlineStyle(os) {}

// Constructeur pour un rectangle ou une ellipse
CustomShape::CustomShape(const QRect &r, ShapeType st, int ot, const QColor &oc, const QColor &fc, Qt::PenStyle os)
    : rect(r), shapeType(st), outlineThickness(ot), outlineColor(oc), fillColor(fc), outlineStyle(os) {}

// Constructeur pour un triangle
CustomShape::CustomShape(const QPolygon &r, ShapeType st, int ot, const QColor &oc, const QColor &fc, Qt::PenStyle os)
    : polygon(r), shapeType(st), outlineThickness(ot), outlineColor(oc), fillColor(fc), outlineStyle(os) {}


bool CustomShape::isInsideEllipse(const QPoint &point) const
{

    if (shapeType != ShapeType::Ellipse) {
        return false;
    }

    // Calculez les demi-axes de l'ellipse

    double a = rect.width() / 2.0;
    double b = rect.height() / 2.0;

    // Trouvez le centre de l'ellipse
    double centerX = rect.left() + a;
    double centerY = rect.top() + b;

    // Calculez la distance entre le point et le centre de l'ellipse
    double xDiff = point.x() - centerX;
    double yDiff = point.y() - centerY;

    qDebug() << (xDiff * xDiff) / (a * a) + (yDiff * yDiff) / (b * b);

    // Vérifiez si le point est à l'intérieur de l'ellipse en utilisant l'équation
    return (xDiff * xDiff) / (a * a) + (yDiff * yDiff) / (b * b) <= 1.0;
}

std::string CustomShape::typeToString() {

    switch (this->shapeType) {
    case Line:
        return "Line";
    case Rectangle:
        return "Rectangle";
    case Triangle:
        return "Triangle";
    case Ellipse:
        return "Ellipse";
    default:
        return "Unknown";
    }
}

bool CustomShape::selectResizeHandle(const QPoint &point) {

    if (shapeType == ShapeType::Rectangle || shapeType == ShapeType::Ellipse) {
        if (resizeHandleTopLeft.contains(point)) {
            currentResizeHandleSelected = ResizeHandle::TopLeft;
            return true;
        }
        if (resizeHandleTopRight.contains(point)) {
            currentResizeHandleSelected = ResizeHandle::TopRight;
            return true;
        }
        if (resizeHandleBottomLeft.contains(point)) {
            currentResizeHandleSelected = ResizeHandle::BottomLeft;
            return true;
        }
        if (resizeHandleBottomRight.contains(point)) {
            currentResizeHandleSelected = ResizeHandle::BottomRight;
            return true;
        }
    } else if (shapeType == ShapeType::Line) {
        if (resizeHandleTop.contains(point)) {
            currentResizeHandleSelected = ResizeHandle::Top;
            return true;
        }
        if (resizeHandleBottom.contains(point)) {
            currentResizeHandleSelected = ResizeHandle::Bottom;
            return true;
        }
    }

    return false; // Aucun resizeHandle sélectionné
}

void CustomShape::drawResizeHandle(QPainter &painter) {

    updateResizeHandle();

    QPen pen(QColor(Qt::white), 2);
    painter.setBrush(QBrush(QColor(Qt::blue)));
    painter.setPen(pen);

    if (shapeType == ShapeType::Rectangle || shapeType == ShapeType::Ellipse) {
        painter.drawRect(resizeHandleTopLeft);
        painter.drawRect(resizeHandleTopRight);
        painter.drawRect(resizeHandleBottomLeft);
        painter.drawRect(resizeHandleBottomRight);
    }

    if (shapeType == ShapeType::Line) {
        painter.drawRect(resizeHandleTop);
        painter.drawRect(resizeHandleBottom);
    }
}

void CustomShape::updateResizeHandle()
{
    int handleSize = 6; // Taille des poignées de redimensionnement

    if (shapeType == ShapeType::Rectangle) {
        resizeHandleTopLeft = QRect(rect.topLeft(), QSize(handleSize, handleSize));
        resizeHandleTopRight = QRect(rect.topRight().x() - handleSize, rect.topRight().y(), handleSize, handleSize);
        resizeHandleBottomLeft = QRect(rect.bottomLeft().x(), rect.bottomLeft().y() - handleSize, handleSize, handleSize);
        resizeHandleBottomRight = QRect(rect.bottomRight().x() - handleSize, rect.bottomRight().y() - handleSize, handleSize, handleSize);
    }

    if (shapeType == ShapeType::Rectangle || shapeType == ShapeType::Ellipse) {
        resizeHandleTopLeft = QRect(rect.topLeft(), QSize(handleSize, handleSize));
        resizeHandleTopRight = QRect(rect.topRight().x() - handleSize, rect.topRight().y(), handleSize, handleSize);
        resizeHandleBottomLeft = QRect(rect.bottomLeft().x(), rect.bottomLeft().y() - handleSize, handleSize, handleSize);
        resizeHandleBottomRight = QRect(rect.bottomRight().x() - handleSize, rect.bottomRight().y() - handleSize, handleSize, handleSize);
    }

    if (shapeType == ShapeType::Line) {
        resizeHandleTop = QRect(line.p1(), QSize(handleSize, handleSize));
        resizeHandleBottom = QRect(line.p2(), QSize(handleSize, handleSize));
    }
}

bool CustomShape::isPointOnLine(const QPoint &point) const {

    int tolerance = 3;

    if (shapeType != ShapeType::Line) {
        return false;
    }

    // Calculez la distance entre le point et la ligne en utilisant une distance de Manhattan
    int x1 = line.x1();
    int y1 = line.y1();
    int x2 = line.x2();
    int y2 = line.y2();

    int distance = std::abs((x2 - x1) * (y1 - point.y()) - (x1 - point.x()) * (y2 - y1)) /
                   std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    // Vérifiez si la distance est inférieure ou égale à la tolérance
    return distance <= tolerance;
}

void CustomShape::resize(const QPoint &point) {


    if (shapeType == ShapeType::Rectangle || shapeType == ShapeType::Ellipse) {
        if (currentResizeHandleSelected == ResizeHandle::TopLeft) {
            // Redimensionner en ajustant le coin supérieur gauche
            // Mettez à jour les coordonnées du coin supérieur gauche
            rect.setTopLeft(point);
        } else if (currentResizeHandleSelected == ResizeHandle::TopRight) {
            // Redimensionner en ajustant le coin supérieur droit
            // Mettez à jour les coordonnées du coin supérieur droit
            rect.setTopRight(point);
        } else if (currentResizeHandleSelected == ResizeHandle::BottomLeft) {
            // Redimensionner en ajustant le coin inférieur gauche
            // Mettez à jour les coordonnées du coin inférieur gauche
            rect.setBottomLeft(point);
        } else if (currentResizeHandleSelected == ResizeHandle::BottomRight) {
            // Redimensionner en ajustant le coin inférieur droit
            // Mettez à jour les coordonnées du coin inférieur droit
            rect.setBottomRight(point);
        }

    } else if (shapeType == ShapeType::Line) {
        if (currentResizeHandleSelected == ResizeHandle::Top) {
            // Redimensionner la ligne en ajustant le point supérieur
            // Mettez à jour les coordonnées du point supérieur de la ligne
            line.setP1(point);
        } else if (currentResizeHandleSelected == ResizeHandle::Bottom) {
            // Redimensionner la ligne en ajustant le point inférieur
            // Mettez à jour les coordonnées du point inférieur de la ligne
            line.setP2(point);
        }
    }

    updateResizeHandle();
}

void CustomShape::move(const QPoint &oldCursorPosition, const QPoint &newCursorPosition) {
    // Calculer le déplacement entre les anciennes et les nouvelles positions du curseur
    QPoint offset = newCursorPosition - oldCursorPosition;

    // Calculer la nouvelle position de la forme
    QPoint newShapePosition;

    if (shapeType == ShapeType::Rectangle || shapeType == ShapeType::Ellipse) {
        // Pour les rectangles et les ellipses, mettez à jour la position du coin supérieur gauche
        newShapePosition = rect.topLeft() + offset;
        rect.moveTo(newShapePosition);
    } else if (shapeType == ShapeType::Line) {
        // Pour les lignes, déplacez les deux points de la ligne
        int dx = offset.x();
        int dy = offset.y();
        line.translate(dx, dy);
    } else if (shapeType == ShapeType::Triangle) {
        // Pour les triangles, déplacez chaque point du polygone
        int dx = offset.x();
        int dy = offset.y();
        for (int i = 0; i < polygon.size(); i++) {
            polygon[i] += QPoint(dx, dy);
        }
    }
}

