// main.qml
import QtQuick 2.2
import Sailfish.Silica 1.0

ApplicationWindow {
    initialPage: Component {
        Page {
            Button {
                text: "Привет!"
                anchors.centerIn: parent
                onClicked: pageStack.push(Qt.resolvedUrl("anotherpage.qml"))
            }
        }
    }
}
