import QtCore
import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: root

    signal openForm()

    function onOpened(){
        controlTournament.list.update();
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15

        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            spacing: 0

            Item { Layout.fillWidth: true }

            Button {
                Layout.preferredWidth: 80
                Layout.preferredHeight: 40
                text: "ADD"
                onClicked: root.openForm()
            }

        }

        ListView {
            id: table
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 1
            model: controlTournament.list

            spacing: 3

            delegate: Rectangle {
                id: item_rec

                width: table.width
                height: 35
                radius: 3

                color: "transparent"

                required property int index;
                required property int m_id;
                required property date m_date;
                required property string m_name;
                required property string m_place;

                RowLayout {
                    anchors.fill: parent
                    spacing: 20

                    Label {
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 120

                        text: m_date
                        font.pixelSize: Qt.application.font.pixelSize * 1.15
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter

                    }

                    Label {
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 200

                        text: m_place
                        font.pixelSize: Qt.application.font.pixelSize * 1.15
                        verticalAlignment: Qt.AlignVCenter
                    }

                    Label {
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true

                        text: m_name
                        font.pixelSize: Qt.application.font.pixelSize * 1.3
                        verticalAlignment: Qt.AlignVCenter
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: enabled
                    onHoveredChanged: {
                        item_rec.color = containsMouse ? "#935b21" : "transparent";
                    }
                    onClicked: {
                        console.log(m_id)
                        controlTournament.edit(m_id);
                        root.openForm();
                    }
                }

            }
        }
    }
}