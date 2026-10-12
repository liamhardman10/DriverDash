import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 1280
    height: 720
    visible: true
    title: "DriverDash"
    color: "#101418"

    // Reads from the C++ side.
    readonly property string greeting: app.greeting

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 32
        spacing: 24

        Text {
            text: root.greeting
            color: "#e6e6e6"
            font.pixelSize: 28
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            text: "Current page: " + app.currentPage
            color: "#9aa4ad"
            font.pixelSize: 18
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 16

            Button {
                text: "Home"
                onClicked: app.currentPage = "home"
            }
            Button {
                text: "Media"
                onClicked: app.currentPage = "media"
            }
            Button {
                text: "Settings"
                onClicked: app.currentPage = "settings"
            }
        }

        Item { Layout.fillHeight: true }

        Button {
            text: "Quit"
            Layout.alignment: Qt.AlignHCenter
            onClicked: app.quit()
        }
    }
}