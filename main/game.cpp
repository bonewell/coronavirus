#include "game.h"

#include <random>

#include "polygonfactory.h"
#include "regularpolygonmodel.h"

Game::Game(PolygonFactory const& factory, RegularPolygonModel& model, QObject *parent)
    : QObject(parent),
      m_factory{factory},
      m_model{model},
      m_size{640.0, 480.0}
{
    connect(&m_model, &RegularPolygonModel::infect, this, &Game::update);
    connect(&m_model, &RegularPolygonModel::kill,
            &m_model, &RegularPolygonModel::killPolygon);
}

void Game::create(QPointF const& hometown, int quantity)
{
    std::random_device generator{};
    std::uniform_real_distribution<> x{0.0, m_size.width()};
    std::uniform_real_distribution<> y{0.0, m_size.height()};

    while (quantity--) {
        m_model.addPolygon(m_factory.create(hometown, {x(generator), y(generator)}));
    }
}

void Game::setSize(QSizeF size)
{
    m_size = std::move(size);
}

void Game::update(int row)
{
    auto hometown = m_model.getPolygon(row).center();
    auto sides = m_model.getPolygon(row).sides();
    m_model.killPolygon(row);
    create(hometown, sides);
}
