import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    readonly property real percent: 0.4

    // id property used in Qml content
    // objectName property used in c++ file
    objectName: "window"

    visible: true

    width: Screen.width*percent
    height: Screen.height*percent
    x:(Screen.width-width)/2
    y:(Screen.height-height)/2

    title: qsTr("How to call Qml object in c++")

    Text {
        objectName: "text"
        anchors.centerIn: parent
        text: qsTr("i am qml text object")
        font.pixelSize: 14
    }

    Button {
        readonly property int marginVal:10

        objectName: "quitbtn"
        anchors.right: parent.right
        anchors.rightMargin: marginVal
        anchors.bottom: parent.bottom
        anchors.bottomMargin: marginVal
        text: qsTr("Quit")
    }
}
