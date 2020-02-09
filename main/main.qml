import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("CoronaVirus")

    RegularPolygon {
        center: Qt.point(parent.width/2, parent.height/2)
        radius: 200
        sides: 3
        color: "blue"
        onTapped: console.log("tapped")
    }
}
