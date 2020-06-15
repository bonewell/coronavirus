#include "regularpolygonmodel.h"

#include "polygonfactory.h"

RegularPolygonModel::RegularPolygonModel(PolygonFactory const& factory,
                                         QObject *parent)
    : QAbstractListModel{parent}, m_factory{factory}
{
}

void RegularPolygonModel::add(RegularPolygon const& polygon)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_polygons << polygon;
    endInsertRows();

//    rowCount(), rowCount()
}

RegularPolygon const& RegularPolygonModel::get(int row)
{
    return m_polygons.at(row);
}

void RegularPolygonModel::remove(int row)
{
    removeRows(row, 1);
}

int RegularPolygonModel::rowCount(QModelIndex const&) const
{
    return m_polygons.count();
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

bool RegularPolygonModel::insertRows(int row, int count, QModelIndex const& parent)
{
    beginInsertRows(parent, row, row + count - 1);
    m_polygons << polygon;
    endInsertRows();
    return true;
}

bool RegularPolygonModel::removeRows(int row, int count, QModelIndex const& parent)
{
    auto begin = m_polygons.begin() + row;
    auto end = begin + count;
    beginRemoveRows(parent, row, row + count - 1);
    m_polygons.erase(begin, end);
    endRemoveRows();
    return true;
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
