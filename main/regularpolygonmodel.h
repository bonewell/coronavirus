#ifndef REGULARPOLYGONMODEL_H
#define REGULARPOLYGONMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>

#include "regularpolygon.h"

class RegularPolygonModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RegularPolygonRoles {
        HometownRole = Qt::UserRole + 1,
        CenterRole,
        RadiusRole,
        SidesRole,
        LifetimeRole
    };

    explicit RegularPolygonModel(QObject* parent = nullptr);
    void add(RegularPolygon const& polygon);
    RegularPolygon const& get(int row);
    void remove(int row);

    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
    QModelIndex parent(QModelIndex const& child) const override;

signals:
    void infect(int row);
    void kill(int row);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<RegularPolygon> m_polygons;
};

#endif // REGULARPOLYGONMODEL_H
