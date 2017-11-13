import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    property real percent: 0.5;

    visible: true

    width: Screen.width*percent;
    height: Screen.height*percent;
    x:(Screen.width-width)/2;
    y:(Screen.height-height)/2;

    title: qsTr("Hello World")
}
