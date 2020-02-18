#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSizeF>
#include <QPointF>

class PolygonFactory;
class RegularPolygonModel;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(PolygonFactory const& factory,
                  RegularPolygonModel& mode,
                  QObject *parent = nullptr);

public:
    void start(int quantity) { create({0, 0}, quantity); }

public slots:
    void setSize(QSizeF size);

private slots:
    void update(int row);

private:
    void create(QPointF const& hometown, int quantity);
    PolygonFactory const& m_factory;
    RegularPolygonModel & m_model;
    QSizeF m_size;
};

#endif // GAME_H
