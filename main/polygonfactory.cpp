#include "polygonfactory.h"

#include <random>

PolygonFactory::PolygonFactory(int lifetime, qreal radius, SideLimits const& limits)
    : m_lifetime{lifetime},
      m_radius{radius},
      m_min{limits.first},
      m_max{limits.second}
{}

RegularPolygon PolygonFactory::create(QPointF const& hometown, QPointF const& location) const
{
    std::random_device generator{};
    std::uniform_int_distribution<> range{m_min, m_max};
    return {hometown, location, m_radius, range(generator), m_lifetime};
}
