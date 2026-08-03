import QtCore
import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: root

    signal closeUnit();

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        TabBar {
            id: bar
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            TabButton {
                text: qsTr("Sensei")
            }
            TabButton {
                text: qsTr("Deshi")
            }
        }

        StackLayout {

            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 1

            currentIndex: bar.currentIndex
            ClubSensei {
                id: club_sensei
                onToList: root.closeUnit();
            }
            ClubSensei {
                id: club_sensei2
            }
        }
    }

}
