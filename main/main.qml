import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("CoronaVirus")

    function randomRotation(max) {
        return Math.floor(Math.random() * Math.floor(max));
    }

    Repeater {
        id: crowd
        model: polygons
        readonly property real duration: 500

        RegularPolygon {
            id: patient
            sides: model.sides

            ColorAnimation on color {
                from: "blue"
                to: "red"
                duration: model.lifetime
                onFinished: {
                    died.action = function () { polygons.kill(index) };
                    died.start();
                }
            }

            PropertyAnimation on center {
                from: model.hometown
                to: model.center
                duration: crowd.duration
            }

            NumberAnimation on radius {
                from: 0.0
                to: model.radius
                duration: crowd.duration
            }

            RotationAnimation on rotation {
                 from: 0; to: randomRotation(270)
                 duration: crowd.duration
                 direction: RotationAnimation.Clockwise
            }

            PropertyAnimation {
                id: died
                property var action
                target: patient
                properties: "radius"
                to: 0
                duration: crowd.duration
                onFinished: action()
            }

            onTapped: {
                died.action = function () { polygons.infect(index) };
                died.start();
            }

//            Component.onCompleted: console.log(model.hometown)
        }
    }
}
