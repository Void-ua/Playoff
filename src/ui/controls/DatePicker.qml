import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts
import QtQml

Item {
    id:root

    width: 140
    height: 40

    readonly property var locale: Qt.locale()
    readonly property var date_format: locale.dateFormat(Locale.ShortFormat)
    readonly property real pos_spacer: root.height * 0.5
    property date selected_date: new Date()
    property string str_date: locale.toString(root.selected_date, root.date_format)
    property bool enabled: true

    TextField {
        id: f_date
        anchors.fill: parent
        // anchors.margins: 5
        rightPadding: root.height
        enabled: root.enabled
        readOnly: true
        text: root.enabled ? root.str_date : ""
        onPressed: p_picker.open();
    }

    ToolButton {
        id: b_picker

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 2
        enabled: root.enabled
        width: root.height - 4
        height: root.height - 4

        text: "\u25BC"
        font.pixelSize: Qt.application.font.pixelSize * 0.7

        onClicked: p_picker.open()
    }

    Popup {
        id: p_picker

        width: Math.max(grid.implicitWidth + 20, 280)
        height: calendar_content.implicitHeight + topPadding + bottomPadding

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        contentItem:  ColumnLayout {
            id: calendar_content

            property int m_year: root.selected_date.getFullYear()
            property int m_month: root.selected_date.getMonth()

            spacing: 3


            RowLayout {
                Layout.fillWidth: true

                ToolButton {
                    Layout.preferredWidth: implicitHeight
                    Layout.preferredHeight: implicitHeight

                    text: "\u276E"
                    font.pixelSize: Qt.application.font.pixelSize * 0.7
                    onClicked: {
                        if (calendar_content.m_month === 0) {
                            calendar_content.m_month = 11;
                            calendar_content.m_year -= 1;
                        } else {
                            calendar_content.m_month -=1;
                        }
                    }
                }
                Label {
                    id: l_month
                    Layout.fillWidth: true

                    text: locale.monthName(calendar_content.m_month, Locale.LongFormat).toUpperCase()
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                }
                ToolButton {
                    Layout.preferredWidth: implicitHeight
                    Layout.preferredHeight: implicitHeight

                    text: "\u276F"
                    font.pixelSize: Qt.application.font.pixelSize * 0.7
                    onClicked: {
                        if (calendar_content.m_month === 11) {
                            calendar_content.m_month = 0;
                            calendar_content.m_year += 1;
                        } else {
                            calendar_content.m_month +=1;
                        }
                    }
                }
            }
            DayOfWeekRow {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                locale: root.locale

            }
            MonthGrid {
                id: grid
                Layout.preferredHeight: implicitHeight
                Layout.fillWidth: true
                locale: root.locale
                month: calendar_content.m_month
                year: calendar_content.m_year
                onClicked: function(date) {
                    root.selected_date = date;
                    p_picker.close()
                }
            }
            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight

                spacing: 7

                Item {
                    Layout.fillWidth: true
                }
                ToolButton {
                    Layout.preferredWidth: implicitHeight
                    Layout.preferredHeight: implicitHeight
                    text: "\u276E"
                    font.pixelSize: Qt.application.font.pixelSize * 0.7
                    onClicked: calendar_content.m_year -= 1;
                }
                Label {
                    id: l_year
                    Layout.preferredWidth: implicitWidth
                    Layout.preferredHeight: implicitHeight
                    text: calendar_content.m_year
                }
                ToolButton {
                    Layout.preferredWidth: implicitHeight
                    Layout.preferredHeight: implicitHeight

                    text: "\u276F"
                    font.pixelSize: Qt.application.font.pixelSize * 0.7
                    onClicked: calendar_content.m_year += 1;
                }
            }
        }
    }
}
