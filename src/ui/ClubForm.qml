import QtCore
import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

import UiPlayoff
import "controls"


Item {
    id: root

    signal closeForm();

    Flickable {
        anchors.fill: parent
        contentHeight: mainLayout.height
        boundsBehavior: Flickable.StopAtBounds

        ColumnLayout {
            id: mainLayout
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(parent.width - 60, Style.formWidth)
            spacing: 0

            Item { height: 15 }
            Label {
                id: l_title
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 20
                font.weight: Font.Bold
                text: "Клуб"
            }
            Item { height: 15 }
            Pane {
                Layout.fillWidth: true

                background: Rectangle {
                    color: {
                        Material.theme === Material.Dark ?
                                    Qt.lighter(Material.background, 1.15) :
                                    Qt.darker(Material.background, 1.05)
                    }
                    radius: 8
                }

                Material.elevation: 3
                padding: 20

                ColumnLayout {
                    anchors.fill: parent
                    spacing: Style.formColSpacing


                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1
                        Layout.margins: 10
                        color: Material.primary
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: Style.formRowSpacing

                        Label {
                            Layout.preferredWidth: 120
                            Layout.preferredHeight: Style.formRowHeight
                            text: "Назва"
                            verticalAlignment: Qt.AlignVCenter
                        }

                        TextField {
                            id: f_name
                            Layout.fillWidth: true
                            Layout.preferredHeight: Style.formRowHeight
                            leftPadding: 15
                            text: controlClub.form.name
                            onTextChanged: controlClub.form.name = text;
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: Style.formRowSpacing

                        Label {
                            Layout.preferredWidth: 120
                            Layout.preferredHeight: Style.formRowHeight
                            text: "Місце знаходження"
                            verticalAlignment: Qt.AlignVCenter
                        }
                        TextField {
                            id: f_location
                            Layout.fillWidth: true
                            Layout.preferredHeight: Style.formRowHeight
                            leftPadding: 15
                            text: controlClub.form.location
                            onTextChanged: controlClub.form.location = text;
                        }
                    }
                }
            }

            Item { height: 24 }

            FormButtons {
                id: form_buttons
                Layout.fillWidth: true
                enableSave: controlClub.form.saveValid
                onDeleteClicked: {
                    controlClub.form.inactivated();
                    root.closeForm();
                }
                onSaveClicked: controlClub.form.post();
                onSaveCloseClicked: {
                    controlClub.form.post();
                    root.closeForm();
                }
                onCloseClicked: root.closeForm();
            }
        }
    }
}
