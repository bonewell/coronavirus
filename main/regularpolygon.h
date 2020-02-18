#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include <QPointF>

class RegularPolygon
{
public:
    RegularPolygon(QPointF hometown, QPointF center,
                   qreal radius, int sides, int lifetime);

    QPointF const& hometown() const;
    QPointF const& center() const;
    qreal radius() const;
    int sides() const;
    int lifetime() const;

private:
    QPointF m_hometown;
    QPointF m_center;
    qreal m_radius;
    int m_sides;
    int m_lifetime;
};

#endif // REGULARPOLYGON_H
