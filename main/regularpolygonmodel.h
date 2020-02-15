#ifndef REGULARPOLYGONMODEL_H
#define REGULARPOLYGONMODEL_H

#include <QAbstractItemModel>
#include <QByteArray>
#include <QHash>
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

class RegularPolygonModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum RegularPolygonRoles {
        CenterRole = Qt::UserRole + 1,
        RadiusRole,
        SidesRole
    };

    explicit RegularPolygonModel(QObject* parent = nullptr);
    void addPolygon(RegularPolygon const& polygon);
    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    int columnCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, QModelIndex const& parent = QModelIndex()) const override;
    QModelIndex parent(QModelIndex const& child) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<RegularPolygon> m_polygons;
};

#endif // REGULARPOLYGONMODEL_H
