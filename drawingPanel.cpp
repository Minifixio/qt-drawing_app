#include "drawingPanel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <toolPanel.h>

DrawingPanel::DrawingPanel(ToolPanel& toolPanel, QWidget *parent)
    : QFrame(parent), toolPanel(toolPanel), lineThickness(1), lineColor(Qt::black), lineStyle(Qt::SolidLine)
{
    this->setMinimumSize(1000, 200);
    this->setStyleSheet("border: 2px solid white; border-radius: 10px;");

    connect(&toolPanel, &ToolPanel::thicknessChanged, this, &DrawingPanel::setThickness);
    connect(&toolPanel, &ToolPanel::colorSelected, this, &DrawingPanel::setColor);
    connect(&toolPanel, &ToolPanel::lineStyleChanged, this, &DrawingPanel::updateLineStyle);

    isDrawing = false;
}

void DrawingPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Pour un rendu plus lisse

    for (const CustomLine &customLine : lines)
    {
        QPen pen(customLine.color, customLine.thickness, customLine.lineStyle);
        painter.setPen(pen);
        painter.drawLine(customLine.line);
    }

    // Dessin de la ligne en cours si l'utilisateur est en train de dessiner
    if (isDrawing)
    {
        QPen pen(lineColor, lineThickness, lineStyle);
        painter.setPen(pen);
        painter.drawLine(currentLine);
    }
}

void DrawingPanel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Commencer un nouveau dessin de ligne
        currentLine.setP1(event->pos());
        currentLine.setP2(event->pos());
        isDrawing = true;
    }
}

void DrawingPanel::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing)
    {
        currentLine.setP2(event->pos());
        update();
    }
}

void DrawingPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        currentLine.setP2(event->pos());

        // Ajout de la nouvelle ligne avec l'épaisseur et la couleur actuelles
        CustomLine customLine(currentLine, lineThickness, lineColor, lineStyle);
        lines.append(customLine);

        currentLine = QLine(); // Réinitialisation la ligne en cours
        isDrawing = false;

        update();
    }
}

void DrawingPanel::setThickness(int thickness)
{
    lineThickness = thickness;
    update();
}

void DrawingPanel::setColor(const QColor& color)
{
    lineColor = color;
    update();
}

void DrawingPanel::updateLineStyle(Qt::PenStyle style)
{
    lineStyle = style;
    update();
}
