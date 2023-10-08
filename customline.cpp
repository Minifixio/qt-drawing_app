#include "customline.h"

CustomLine::CustomLine(const QLine& line, int thickness, const QColor& color, const Qt::PenStyle lineStyle)
    : line(line), thickness(thickness), color(color), lineStyle(lineStyle)
{
}
