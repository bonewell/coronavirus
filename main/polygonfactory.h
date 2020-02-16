#ifndef POLYGONFACTORY_H
#define POLYGONFACTORY_H

#include <QtGlobal>
#include <QPointF>

#include <utility>

#include "regularpolygon.h"

class PolygonFactory {
public:
    using SideLimits = std::pair<int, int>;

    PolygonFactory(qreal radius, SideLimits const& limits);
    RegularPolygon create(QPointF const& location) const;

private:
    qreal m_radius;
    int m_min;
    int m_max;
};

#endif // POLYGONFACTORY_H
