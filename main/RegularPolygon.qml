import QtQuick 2.14
import QtQuick.Shapes 1.12

Shape {
    id: root

    property point center
    property real radius
    property int sides
    property alias color: shape.fillColor

    function points(center, radius, sides) {
        if (sides < 3) return [];

        let angle = 2 * Math.PI / sides;
        return Array.from({ length: sides },
                          (_, i) => {
                              let rotation = angle * i;
                              return Qt.point(
                                  center.x + radius * Math.cos(rotation),
                                  center.y + radius * Math.sin(rotation))
                          });
    }

    ShapePath {
        id: shape
        strokeWidth: 0
        PathPolyline { path: points(center, radius, sides) }
    }
}
