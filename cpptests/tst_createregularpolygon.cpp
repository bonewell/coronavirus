#include <QtTest>

#include <random>
#include <utility>

#include "../main/polygonfactory.h"

class CreateRegularPolygon : public QObject
{
    Q_OBJECT

private slots:
    void test_createRegularPolygon();
};

void CreateRegularPolygon::test_createRegularPolygon()
{
    auto polygon = PolygonFactory{5000, 50, {3, 7}}.create({10, 10}, {200, 200});

    QCOMPARE(polygon.hometown(), QPointF(10, 10));
    QCOMPARE(polygon.center(), QPointF(200, 200));
    QCOMPARE(polygon.radius(), 50);
    QVERIFY(polygon.sides() >= 3 && polygon.sides() <= 7);
    QCOMPARE(polygon.lifetime(), 5000);
}

QTEST_APPLESS_MAIN(CreateRegularPolygon)

#include "tst_createregularpolygon.moc"
