#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include <QPointF>

class RegularPolygon
{
public:
    RegularPolygon(QPointF center, qreal radius, int sides);

    QPointF center() const;
    qreal radius() const;
    int sides() const;

private:
    QPointF m_center;
    qreal m_radius;
    int m_sides;
};

#endif // REGULARPOLYGON_H
