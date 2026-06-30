import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import Workstock 1.0

Popup {
    id: popup
    objectName: "myPopup"
    parent: Overlay.overlay

    property int typeNote: Workstock.NoteType.kNotify
    property string textNote: ""

    closePolicy: Popup.NoAutoClose
    x: 10
    y: 10
    z: 10
    width: 400
    height: 70
    modal: false
    dim: false
    padding: 0
    opacity: .8

    readonly property color noteColor: {
        switch(typeNote) {
            case Workstock.NoteType.kSuccess: return Material.color(Material.Green, Material.Shade700) //"#6AA84F"
            case Workstock.NoteType.kError: return Material.color(Material.Pink, Material.Shade700) //"#F44336"
            default: return Material.color(Material.Cyan, Material.Shade700) //"#3D85C6"
        }
    }

    readonly property int displayDuration: {
        switch(typeNote) {
            case Workstock.NoteType.kSuccess: return 2000
            case Workstock.NoteType.kError: return 7000
            default: return 3500
        }
    }

    Rectangle {
        anchors.fill: parent
        radius: 5
        color: Material.background
        opacity: .8

        RowLayout {
            anchors.fill: parent
            anchors.margins: 15
            spacing: 10

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: 5
                color: popup.noteColor
            }

            Text {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: textNote
                color: popup.noteColor
                font.pixelSize: Qt.application.font.pixelSize * 1.2
                wrapMode: Text.WordWrap
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
            }
        }
    }

    Timer {
        running: true
        repeat: false
        interval: popup.displayDuration
        onTriggered: popup.close()
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 200 }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 200 }
    }

    Component.onCompleted: {
        open()
    }
}
