import QtQuick 2.0

Rectangle {
    id: root

    property int died
    property int recovered
    property int total

    Text {
        id: died
        text: "Died: " + root.died
        font.pointSize: 22
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: recovered
        text: "Recovered: " + root.recovered
        font.pointSize: 22
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: died.bottom
    }

    Text {
        id: total
        text: "Total: " + root.total
        font.pointSize: 22
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: recovered.bottom
    }

    Text {
        id: win
        text: root.recovered > root.died ? "You won!" : "You lose!"
        color: root.recovered > root.died ? "green" : "red"
        font.pointSize: 32
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: total.bottom
    }
}
