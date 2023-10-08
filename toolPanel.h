#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <QColor>
#include <QColorDialog>
#include <QFrame>
#include <QLabel>
#include <qwidget.h>

class ToolPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ToolPanel(QWidget *parent = nullptr);

private:
    QFrame* colorDisplay;
    QLabel* thicknessLabel;

signals:
    void colorSelected(const QColor& color);
    void thicknessChanged(int thickness);
    void lineStyleChanged(Qt::PenStyle style);

private slots:
    void handleThicknessChanged(int thickness);
    void chooseColor();
    void handleLineStyleChanged(bool dashed);

};

#endif // TOOLPANEL_H
