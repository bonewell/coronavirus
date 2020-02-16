#include "regularpolygon.h"

RegularPolygon::RegularPolygon(QPointF center, qreal radius, int sides)
    : m_center{center}, m_radius{radius}, m_sides{sides}
{
}

QPointF RegularPolygon::center() const
{
    return m_center;
}

qreal RegularPolygon::radius() const
{
    return m_radius;
}

int RegularPolygon::sides() const
{
    return m_sides;
}
