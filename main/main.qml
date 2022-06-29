import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("CoronaVirus")

    property int amount_died: 0
    property int amount_recovered: 0
    property int amount_infected: 0

    function randomRotation(max) {
        return Math.floor(Math.random() * Math.floor(max));
    }

    Repeater {
        id: crowd

        readonly property real duration: 500

        model: polygons

        RegularPolygon {
            id: patient
            z: -index
            sides: model.sides

            ColorAnimation on color {
                from: "blue"
                to: "red"
                duration: model.lifetime
                onFinished: {
                    extinction.action = function () {
                        root.amount_died += 1;
                        polygons.kill(index);
                    };
                    extinction.start();
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
                id: extinction
                property var action
                target: patient
                properties: "radius"
                to: 0
                duration: crowd.duration
                onFinished: action()
            }

            onTapped: {
                extinction.action = function () {
                    root.amount_recovered += 1;
                    root.amount_infected += sides - 2; // min sides is 3
                    polygons.infect(index);
                };
                extinction.start();
            }
        }
    }

    Score {
        visible: !crowd.count && root.amount_infected
        anchors.horizontalCenter: parent.horizontalCenter

        died: root.amount_died
        recovered: root.amount_recovered
        total: root.amount_infected
    }

    Button {
        id: button
        visible: !crowd.count
        anchors.centerIn: parent
        padding: 20
        color: "green"
        border.color: "lightgreen"
        text: "Play"

        onTapped: {
            root.amount_died = 0;
            root.amount_recovered = 0
            root.amount_infected = 1
            polygons.infect(-1)
        }
    }
}
