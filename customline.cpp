#include "customLine.h"

// Constructeur par défaut
CustomLine::CustomLine() {}

CustomLine::CustomLine(const QLine& line, int thickness, const QColor& color, const Qt::PenStyle lineStyle)
    : line(line), thickness(thickness), color(color), lineStyle(lineStyle)
{
}

