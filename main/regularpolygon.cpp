#include "regularpolygon.h"

RegularPolygon::RegularPolygon(QPointF hometown, QPointF center, qreal radius, int sides, int lifetime)
    : m_hometown{std::move(hometown)},
      m_center{std::move(center)},
      m_radius{radius},
      m_sides{sides},
      m_lifetime{lifetime}
{
}

QPointF const& RegularPolygon::hometown() const
{
    return m_hometown;
}

QPointF const& RegularPolygon::center() const
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

int RegularPolygon::lifetime() const
{
    return m_lifetime;
}


