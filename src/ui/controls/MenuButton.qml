import QtQuick 2.15
import QtQuick.Controls.Material

Item {

    id: root

    signal clicked(i:int)

    property int b_index: 0
    property string b_title: "Title"
    property string b_img: ""

    property int min_width: 50

    Rectangle {
        id: bg
        anchors.fill: parent
        color: Material.background

        Label {
            id: title
            visible: root.width > root.min_width;
            anchors.centerIn: bg
            text: root.b_title
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onHoveredChanged: {
            // bg.border.color = containsMouse ? Material.accent : Material.primary;
            title.color = containsMouse ? Material.accent : Material.foreground
        }
        onClicked: root.clicked(root.b_index)
    }
}
