import QtCore
import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: root


    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        TabBar {
            id: bar
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            TabButton {
                text: qsTr("Tournaments")
            }
            TabButton {
                text: qsTr("Clubs")
            }
        }

        StackLayout {

            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 1

            currentIndex: bar.currentIndex
            Tour {
                id: tour
            }
            Club {
                id: club
            }
        }
    }



}