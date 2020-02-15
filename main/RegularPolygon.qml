import QtQuick 2.14
import QtQuick.Shapes 1.12

Shape {
    id: root

    signal tapped()

    property point center
    property real radius
    property int sides
    property alias color: shape.fillColor

    function points() {
        if (sides < 3) return [];

        let angle = 2 * Math.PI / sides;
        return Array.from({ length: sides },
                          (_, i) => {
                              let rotation = angle * i;
                              return Qt.point(
                                  radius + radius * Math.cos(rotation),
                                  radius + radius * Math.sin(rotation))
                          });
    }

    /**
     * Calculates distance between the center and a point of the side where
     * a ray crosses the side.
     * The ray begins in center and goes through a point of the event of the mouse.
     */
    function limit(X, Y) {
        let angle = 2 * Math.PI / sides;
        let angleA = Math.atan2(Y, X) % angle;
        let angleB = (Math.PI - angle) / 2;
        return radius * Math.sin(angleB) / Math.sin(angleA + angleB);
    }

    function inside(point) {
        let X = point.x - radius;
        let Y = Math.abs(point.y - radius);
        return Math.pow(X, 2) + Math.pow(Y, 2) <= Math.pow(limit(X, Y), 2)
    }

    x: center.x - radius
    y: center.y - radius
    width: 2 * radius
    height: 2 * radius

    ShapePath {
        id: shape
        strokeWidth: 0
        PathPolyline { path: points() }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: if (inside(mouse)) parent.tapped();
    }
}
