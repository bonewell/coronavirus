#include "regularpolygonmodel.h"

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

RegularPolygonModel::RegularPolygonModel(QObject *parent)
    : QAbstractItemModel{parent}
{
}

void RegularPolygonModel::addPolygon(RegularPolygon const& polygon)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_polygons << polygon;
    endInsertRows();
}

int RegularPolygonModel::rowCount(QModelIndex const&) const
{
    return m_polygons.count();
}

int RegularPolygonModel::columnCount(QModelIndex const&) const
{
    return 0;
}

QVariant RegularPolygonModel::data(QModelIndex const& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_polygons.count())
        return QVariant();

    const auto& polygon = m_polygons[index.row()];
    if (role == CenterRole)
        return polygon.center();
    else if (role == RadiusRole)
        return polygon.radius();
    else if (role == SidesRole)
        return polygon.sides();
    return QVariant();
}

QModelIndex RegularPolygonModel::index(int row, int column, QModelIndex const&) const
{
    return createIndex(row, column);
}

QModelIndex RegularPolygonModel::parent(QModelIndex const&) const
{
    return {};
}

QHash<int, QByteArray> RegularPolygonModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[CenterRole] = "center";
    roles[RadiusRole] = "radius";
    roles[SidesRole] = "sides";
    return roles;
}
