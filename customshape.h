#ifndef CUSTOMSHAPE_H
#define CUSTOMSHAPE_H

#include <QColor>
#include <QLine>
#include <QPolygon>
#include <QRect>
#include <ShapeType.h>
#include <QPainter.h>
#include <resizeHandle.h>

class CustomShape
{
public:
    QRect rect; // Le rectangle ou la forme que vous dessinez (pour les rectangles et ellipse)
    QPolygon polygon; // Le polygone (pour les triangles)
    QLine line;

    ShapeType shapeType; // Le type de forme (Rectangle, Triangle, Ellipse, etc.)

    int outlineThickness;
    QColor outlineColor;
    Qt::PenStyle outlineStyle;

    QColor fillColor; // La couleur de la forme
    bool isFilled = false; // Un indicateur pour indiquer si la forme doit être remplie

    // Les indicateurs de redimensionnement pour le rectangle ou l'ellipse
    QRect resizeHandleTopLeft;
    QRect resizeHandleTopRight;
    QRect resizeHandleBottomLeft;
    QRect resizeHandleBottomRight;

    // Les indicateurs pour la ligne
    QRect resizeHandleTop;
    QRect resizeHandleBottom;

    ResizeHandle currentResizeHandleSelected;

    // Constructeur par défaut
    CustomShape();

    // Constructeur pour un rectangle ou un ellipse
    CustomShape(const QRect &r, ShapeType st, int ot, const QColor &oc, const QColor &fc, Qt::PenStyle os);

    // Constructeur pour un rectangle ou un ellipse
    CustomShape(const QLine &r, ShapeType st, int ot, const QColor &oc, const QColor &fc, Qt::PenStyle os);

    // Constructeur pour un rectangle ou un ellipse
    CustomShape(const QPolygon &r, ShapeType st, int ot, const QColor &oc, const QColor &fc, Qt::PenStyle os);

public slots:
    bool isInsideEllipse(const QPoint &point) const;
    bool selectResizeHandle(const QPoint &point);
    bool isPointOnLine(const QPoint &point) const;
    void drawResizeHandle(QPainter &painter);
    void updateResizeHandle();
    void resize(const QPoint &point);
    std::string typeToString();
    void move(const QPoint &oldCursorPosition, const QPoint &newCursorPosition);

};

#endif // CUSTOMSHAPE_H
