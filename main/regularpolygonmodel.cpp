#include "regularpolygonmodel.h"

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

RegularPolygon const& RegularPolygonModel::getPolygon(int row)
{
    return m_polygons.at(row);
}

void RegularPolygonModel::removePolygon(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_polygons.removeAt(row);
    endRemoveRows();
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
    if (role == HometownRole)
        return polygon.hometown();
    else if (role == CenterRole)
        return polygon.center();
    else if (role == RadiusRole)
        return polygon.radius();
    else if (role == SidesRole)
        return polygon.sides();
    else if (role == LifetimeRole)
        return polygon.lifetime();
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
    roles[HometownRole] = "hometown";
    roles[CenterRole] = "center";
    roles[RadiusRole] = "radius";
    roles[SidesRole] = "sides";
    roles[LifetimeRole] = "lifetime";
    return roles;
}
