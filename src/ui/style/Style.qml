pragma Singleton

import QtQuick 2.15

QtObject {

    readonly property int fontSize_8: Qt.application.font.pixelSize * 0.8
    readonly property int fontSize_9: Qt.application.font.pixelSize * 0.9
    readonly property int fontSize_11: Qt.application.font.pixelSize * 1.1
    readonly property int fontSize_12: Qt.application.font.pixelSize * 1.2
    readonly property int fontSize_15: Qt.application.font.pixelSize * 1.5

    //form
    readonly property int formWidth: 600

    readonly property int formColSpacing: 10
    readonly property int formRowSpacing: 5
    readonly property int formRowHeight: 35

    //list

    readonly property int listMargins: 15
    readonly property int listSpacing: 10
    readonly property int listRowHeight: 35
    readonly property int listRowSpacing: 10
    readonly property int listSearchPadding: 25

    //table
    readonly property int tableDelegateHeight: 30
    readonly property int tableSpacing: 3
    readonly property int tableRowSpacing: 10
    readonly property int tableRowHeight: 25


}
