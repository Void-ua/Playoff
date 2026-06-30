import QtCore
import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: root

    signal open()

    Label {
        anchors.centerIn: parent
        font.pixelSize: Qt.application.font.pixelSize * 3.0
        text: "Playoff"
    }

    MouseArea {
        anchors.fill: parent
        onClicked:  root.open()
    }

}