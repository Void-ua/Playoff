import QtCore
import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: root

    signal openForm()
    signal closeUnit()

    function onOpened(){
        controlSensei.list.update();
    }


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 15

        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            spacing: 0

            Button {
                Layout.preferredWidth: 80
                Layout.preferredHeight: 40
                text: "CLUB LIST"
                onClicked: {
                    root.closeUnit();
                }
            }

            Item { Layout.fillWidth: true }

            Button {
                Layout.preferredWidth: 80
                Layout.preferredHeight: 40
                text: "ADD"
                onClicked: {
                    controlClub.edit(0);
                    root.openForm();
                }
            }

        }

        ListView {
            id: table
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.verticalStretchFactor: 1
            model: controlSensei.list

            spacing: 3

            delegate: Rectangle {
                id: item_rec

                width: table.width
                height: 35
                radius: 3

                color: "transparent"

                required property int index;
                required property int m_id;
                required property string m_name;

                RowLayout {
                    anchors.fill: parent
                    spacing: 20

                    Label {
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 50

                        text: m_id
                        font.pixelSize: Qt.application.font.pixelSize * 1.15
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter

                    }

                    Label {
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true

                        text: m_name
                        font.pixelSize: Qt.application.font.pixelSize * 1.15
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter

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
                        controlSensei.edit(m_id);
                        root.openForm();
                    }
                }
            }
        }
    }
}
