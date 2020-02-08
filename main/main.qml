import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RegularPolygon {
        center: Qt.point(parent.width/2, parent.height/2)
        radius: 50
        sides: 5
        color: "blue"
    }
}
