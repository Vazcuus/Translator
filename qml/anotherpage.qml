// AnotherPage.qml
import QtQuick 2.2
import Sailfish.Silica 1.0

Page {
    Button {
        text: "Закрыть эту страницу"
        onClicked: pageStack.pop()
    }
}
