import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("CoronaVirus")

    Repeater {
        model: polygons

        RegularPolygon {
            center: model.center
            radius: model.radius
            sides: model.sides
            color: "blue"
            onTapped: {
                polygons.infect(index);
            }
        }
    }
}
