#ifndef CUSTOMLINE_H
#define CUSTOMLINE_H

#include <QColor>
#include <QLine>



class CustomLine
{

public:
    CustomLine();
    CustomLine(const QLine& line, int thickness, const QColor& color, const Qt::PenStyle lineStyle);
    QLine line;
    int thickness;
    QColor color;
    Qt::PenStyle lineStyle;
};

#endif // CUSTOMLINE_H
