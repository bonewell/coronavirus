import QtQuick 2.14

Rectangle {
    id: root

    signal tapped()

    property alias text: text.text
    property int padding: 0

    width: text.width + padding
    height: text.height + padding
    border.width: 2
    radius: 10

    Text {
        id: text
        color: "white"
        font.pointSize: 32
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: root.tapped();
    }
}
