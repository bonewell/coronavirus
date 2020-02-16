#include "polygonfactory.h"

#include <random>

PolygonFactory::PolygonFactory(qreal radius, SideLimits const& limits)
    : m_radius{radius},
      m_min{limits.first},
      m_max{limits.second}
{}

RegularPolygon PolygonFactory::create(QPointF const& location) const
{
    std::random_device generator{};
    std::uniform_int_distribution<> range{m_min, m_max};
    return {location, m_radius, range(generator)};
}
