import QtQuick 2.0
import QtTest 1.0

TestCase {
    name: "CalculatePoints"

    function points(center, radius, sides) {
        if (sides < 3) return [];

        let angle = 2 * Math.PI / sides;
        return Array.from({ length: sides },
                          (_, i) => Qt.point(radius * Math.cos(angle * i),
                                             radius * Math.sin(angle * i)));
    }

    function test_points_data() {
        return [
            {tag:"2-gon", center: Qt.point(0, 0), radius: 2, sides: 2, answer: []},

            {tag:"3-gon", center: Qt.point(0, 0), radius: 2, sides: 3,
                        answer: [Qt.point(2, 0),
                                 Qt.point(-1, 1.73205),
                                 Qt.point(-1, -1.73205)]},

            {tag:"4-gon", center: Qt.point(0, 0), radius: 3, sides: 4,
                        answer: [Qt.point(3, 0), Qt.point(0, 3),
                                 Qt.point(-3, 0), Qt.point(0, -3)]},

            {tag:"6-gon", center: Qt.point(0, 0), radius: 4, sides: 6,
                        answer: [Qt.point(4, 0), Qt.point(2, 3.4641),
                                 Qt.point(-2, 3.4641), Qt.point(-4, 0),
                                 Qt.point(-2, -3.4641), Qt.point(2, -3.4641)]},
        ];
    }

    function test_points(data) {
        compare(points(data.center, data.radius, data.sides), data.answer);
    }
}
