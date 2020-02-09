import QtQuick 2.0
import QtTest 1.0

import "../main"

RegularPolygon {
    id: root

    SignalSpy {
        id: tap
        target: root
        signalName: "tapped"
    }

    TestCase {
        name: "CalculatePoints"
        when: windowShown

        function test_points_data() {
            return [
                {tag:"2-gon", radius: 2, sides: 2, answer: []},

                {tag:"3-gon", radius: 2, sides: 3,
                            answer: [Qt.point(4, 2), Qt.point(1, 3.73205),
                                     Qt.point(1, 0.267949)]},

                {tag:"4-gon", radius: 3, sides: 4,
                            answer: [Qt.point(6, 3), Qt.point(3, 6),
                                     Qt.point(0, 3), Qt.point(3, 0)]},

                {tag:"6-gon", radius: 4, sides: 6,
                            answer: [Qt.point(8, 4), Qt.point(6, 7.4641),
                                     Qt.point(2, 7.4641), Qt.point(0, 4),
                                     Qt.point(2, 0.535898), Qt.point(6, 0.535898)]}
            ];
        }

        function test_points(data) {
            root.radius = data.radius;
            root.sides = data.sides;

            compare(root.points(), data.answer);
        }

        function test_inside_data() {
            return [
                {tag:"point is inside 3-gon", radius: 2, sides: 3,
                    point: Qt.point(2, 2), answer: true},

                {tag:"point is outside 3-gon", radius: 2, sides: 3,
                    point: Qt.point(3, 1), answer: false},
            ];
        }

        function test_inside(data) {
            root.radius = data.radius;
            root.sides = data.sides;

            compare(inside(data.point), data.answer);
        }

        function test_tap() {
            root.radius = 3;
            root.sides = 3;

            tap.clear();
            mouseClick(root, 4, 2);
            tap.wait();

            compare(tap.count, 1)
        }
    }
}
