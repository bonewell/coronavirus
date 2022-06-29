#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QRect>
#include <QPointF>

class PolygonFactory;
class RegularPolygonModel;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(int quantity,
                  PolygonFactory const& factory,
                  RegularPolygonModel& mode,
                  QObject *parent = nullptr);

public:
    void start(int quantity) { create({0, 0}, quantity); }

public slots:
    void setSize(QSize const& size);

private slots:
    void infected(int row);
    void killed(int row);

private:
    void create(QPointF const& hometown, int quantity);
    int m_quantity;
    PolygonFactory const& m_factory;
    RegularPolygonModel & m_polygons;
    QRectF m_box;
    int m_amount_recovered;
    int m_amount_infected;
};

#endif // GAME_H
