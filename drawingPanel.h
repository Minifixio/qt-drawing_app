#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <CustomLine.h>
#include <QFrame>
#include <QWidget>
#include <ToolPanel.h>

class DrawingPanel : public QFrame
{
    Q_OBJECT
public:
    explicit DrawingPanel(ToolPanel& toolPanel, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    ToolPanel& toolPanel;
    int lineThickness;
    QColor lineColor;
    Qt::PenStyle lineStyle;
    QVector<CustomLine> lines; // Pour stocker les lignes dessinées
    QLine currentLine; // Pour stocker la ligne en cours de dessin
    bool isDrawing; // Variable pour suivre si l'utilisateur est en train de dessiner

public slots:
    void setThickness(int thickness);
    void setColor(const QColor& color);
    void updateLineStyle(Qt::PenStyle style);
};

#endif // DRAWINGPANEL_H
