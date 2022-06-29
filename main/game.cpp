#include "game.h"

#include <random>

#include "polygonfactory.h"
#include "regularpolygonmodel.h"

Game::Game(PolygonFactory const& factory, RegularPolygonModel& model, QObject *parent)
    : QObject(parent),
      m_factory{factory},
      m_polygons{model},
      m_box{0.0, 0.0, 640.0, 480.0},
      m_amount_recovered{0},
      m_amount_infected{0}
{
    connect(&m_polygons, &RegularPolygonModel::infect, this, &Game::infected);
    connect(&m_polygons, &RegularPolygonModel::kill, this, &Game::killed);
    setSize({640, 480});
}

void Game::create(QPointF const& hometown, int quantity)
{
    std::random_device generator{};
    std::uniform_real_distribution<> x{m_box.x(), m_box.width()};
    std::uniform_real_distribution<> y{m_box.y(), m_box.height()};

    m_amount_infected += quantity;
    while (quantity--) {
        m_polygons.add(m_factory.create(hometown, {x(generator), y(generator)}));
    }
}

void Game::setSize(QSize const& size)
{
    auto radius = m_factory.radiusOfPolygon();
    QPointF left_top{radius, radius};
    QPointF bottom_right{size.width() - radius, size.height() - radius};
    m_box = QRectF{left_top, bottom_right};
}

void Game::infected(int row)
{
    m_amount_recovered += 1;
    auto hometown = m_polygons.get(row).center();
    auto sides = m_polygons.get(row).sides();
    m_polygons.remove(row);
    create(hometown, sides - 2); // min sides is 3
}

void Game::killed(int row)
{
    m_polygons.remove(row);
    if (m_polygons.rowCount() == 0)
    {
        qInfo() << "Died: " << m_amount_infected - m_amount_recovered;
        qInfo() << "Recovered: " << m_amount_recovered;
        qInfo() << "Total: " << m_amount_infected;
    }
}
