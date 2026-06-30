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
                text: "Турнир"
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
                            Layout.preferredWidth: implicitWidth
                            Layout.preferredHeight: Style.formRowHeight
                            text: "Name"
                        }

                        TextField {
                            id: f_name
                            Layout.fillWidth: true
                            Layout.preferredHeight: Style.formRowHeight
                            placeholderText: "Name:"
                            leftPadding: 15
                            text: controlTournament.form.name
                            onTextChanged: controlTournament.form.name = text;
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: Style.formRowSpacing

                        Label {
                            Layout.preferredWidth: implicitWidth
                            Layout.preferredHeight: Style.formRowHeight
                            text: "Place"
                        }
                        TextField {
                            id: f_place
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: Style.formRowHeight
                            placeholderText: qsTr("Place")
                            leftPadding: 15
                            text: controlTournament.form.place
                            onTextChanged: controlTournament.form.place = text;
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: Style.formRowSpacing

                        Label {
                            text: qsTr("Date")
                            font.pixelSize: Style.fontSize_9
                        }
                        DatePicker {
                            id: f_tdate
                            Layout.preferredWidth: 140
                            Layout.preferredHeight: Style.formRowHeight
                            selected_date: controlTournament.form.tdate
                            onSelected_dateChanged: controlTournament.form.tdate = selected_date;
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: Style.formRowSpacing

                        Label {
                            Layout.preferredWidth: implicitWidth
                            Layout.preferredHeight: Style.formRowHeight
                            text: "Referre"
                        }
                        TextField {
                            id: f_referre
                            Layout.fillWidth: true
                            Layout.preferredHeight: Style.formRowHeight
                            leftPadding: 15
                            text: controlTournament.form.referre
                            onTextChanged: controlTournament.form.referre = text;
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: Style.formRowSpacing

                        Label {
                            Layout.preferredWidth: implicitWidth
                            Layout.preferredHeight: Style.formRowHeight
                            text: "Secretary"
                        }
                        TextField {
                            id: f_secretary
                            Layout.fillWidth: true
                            Layout.preferredHeight: Style.formRowHeight
                            leftPadding: 15
                            text: controlTournament.form.secretary
                            onTextChanged: controlTournament.form.secretary = text;
                        }
                    }
                }
            }

            Item { height: 24 }

            FormButtons {
                id: form_buttons
                Layout.fillWidth: true
                enableSave: controlTournament.form.saveValid
                onDeleteClicked: {
                    controlTournament.form.inactivated();
                    root.closeForm();
                }
                onSaveClicked: controlTournament.form.post();
                onSaveCloseClicked: {
                    controlTournament.form.post();
                    root.closeForm();
                }
                onCloseClicked: root.closeForm();
            }
        }
    }
}
