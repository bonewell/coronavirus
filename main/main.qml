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
    property int amount_infected: 1

    function randomRotation(max) {
        return Math.floor(Math.random() * Math.floor(max));
    }

    Repeater {
        id: crowd
        model: polygons
        readonly property real duration: 500

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

    Column {
        visible: !crowd.count
        Text {
            id: died
            text: "Died: " + root.amount_died
            font.pointSize: 22
        }
        Text {
            id: recovered
            text: "Recovered: " + root.amount_recovered
            font.pointSize: 22
        }
        Text {
            id: total
            text: "Total: " + root.amount_infected
            font.pointSize: 22
        }
        Text {
            id: win
            text: root.amount_recovered > root.amount_died ? "You won!" : "You lose!"
            color: root.amount_recovered > root.amount_died ? "green" : "red"
            font.pointSize: 32
        }
    }
}
