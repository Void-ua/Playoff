import QtCore
import QtQuick 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts

Item {
    id: root

    signal toList();

    states: [
        State {
            name: "LIST"
            PropertyChanges {}
            StateChangeScript {
                script: {
                    preLoader.sourceComponent = list
                }
            }
        },
        State {
            name: "FORM"
            PropertyChanges {}
            StateChangeScript {
                script: {
                    preLoader.sourceComponent = form
                }
            }
        }
    ]

    state: "LIST"

    StackLayout {
        id: club_stack
        anchors.fill: parent
        currentIndex: 0

        Loader {
            id: preLoader
            active: true
            asynchronous: true
            onLoaded: {
                if (item) {
                    if (item.onOpened) item.onOpened();
                    if (item.openForm) {
                        item.openForm.connect(function(data){ root.state = "FORM" })
                    }
                    if (item.closeForm) {
                        item.closeForm.connect(function(data){ root.state = "LIST"})
                    }
                    if (item.closeUnit) {
                        item.closeUnit.connect(function(data){ root.toList()})
                    }
                }
            }
        }
    }

    Component {
        id: list
        ClubSenseiList {}
    }

    Component {
        id: form
        ClubForm {}
    }

}
