import QtCore
import QtQuick
import QtQuick.Controls.Material

import UiPlayoff 1.0

ApplicationWindow {
    id: app_window
    width: 1200
    height: 750
    visible: true
    title: qsTr("Playoff")

    Material.theme: Material.System
    Material.accent: Material.color(Material.LightGreen, Material.Shade600)

    WelcomePage {
        id: welcome
        anchors.fill: parent
    }

    App {
        id: app
        anchors.fill: parent
        visible: false
    }

    Connections {
        target: welcome
        function onOpen() {
            app.visible = true
            welcome.visible = false
        }
    }

    Settings {
        category: "window"
        property alias x: app_window.x
        property alias y: app_window.y
        property alias width: app_window.width
        property alias height: app_window.height
    }

    // onWidthChanged: notes.updatePositions()
    // onHeightChanged: notes.updatePositions()
}
