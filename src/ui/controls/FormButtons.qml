import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts
import Playoff


Item {
    id: root

    property bool enableDelete: true
    property bool enableSave: true

    signal deleteClicked();
    signal saveClicked();
    signal saveCloseClicked();
    signal closeClicked();

    width: 600
    height: 40

    RowLayout {
        anchors.fill: parent
        spacing: Style.formRowSpacing

        Button {
            id: but_del
            Layout.preferredWidth: 100
            Layout.preferredHeight: Style.formRowHeight
            Material.roundedScale: Material.ExtraSmallScale
            enabled: root.enableDelete;
            text: qsTr("Delete")
            font.weight: Font.Medium
            onClicked: root.deleteClicked();
        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            id: but_save
            Layout.preferredWidth: 80
            Layout.preferredHeight: Style.formRowHeight
            Material.roundedScale: Material.ExtraSmallScale
            enabled: root.enableSave
            text: qsTr("Save")
            highlighted: true
            font.weight: Font.Medium
            onClicked: root.saveClicked();
        }
        Button {
            id: but_save_close
            Layout.preferredWidth: 140
            Layout.preferredHeight: Style.formRowHeight
            Material.roundedScale: Material.ExtraSmallScale
            enabled: root.enableSave
            text: qsTr("Save & Close")
            highlighted: true
            font.weight: Font.Medium
            onClicked: root.saveCloseClicked();
        }
        Button {
            id: but_close
            Layout.preferredWidth: 100
            Layout.preferredHeight: Style.formRowHeight
            Material.roundedScale: Material.ExtraSmallScale
            text: qsTr("Close")
            font.weight: Font.Medium
            onClicked: root.closeClicked();
        }
    }
}
