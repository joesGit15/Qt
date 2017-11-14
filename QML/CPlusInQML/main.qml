import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import joe.qt.ColorMaker 1.0

Window {
    property real percent: 0.6

    visible: true

    width: Screen.width*percent
    height: Screen.height*percent
    x:(Screen.width-width)/2
    y:(Screen.height-height)/2
    title: qsTr("How to use c++ class in QML")

    ColorMaker { id: id_colorMaker }
    Component.onCompleted: {
        id_colorMaker.color = Qt.rgba(0,180,120,255);
        id_colorMaker.setAlgorithm(ColorMaker.LinearIncrease);
    }

    Column {
        property int hval: 50
        anchors.fill: parent

        Text {
            id: id_text
            width: parent.width
            height:parent.hval
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            Connections {
                target: id_colorMaker
                onCurrentTime:{
                    id_text.text = strTime;
                    id_text.color = id_colorMaker.timeColor;
                }
            }
        }

        Rectangle {
            width: parent.width
            height:parent.height - 2*parent.hval
            color: id_colorMaker.color
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            height:parent.hval

            spacing: 10
            topPadding: (parent.hval - id_btnStart.height)/2

            ComboBox {
                currentIndex: 0
                width:150
                model: ListModel {
                    id: id_model
                    ListElement {text:"RandomRGB"}
                    ListElement {text:"RandomRed"}
                    ListElement {text:"RandomGreen"}
                    ListElement {text:"RandomBlue"}
                    ListElement {text:"LinearIncrease"}
                }

                onCurrentIndexChanged: {
                    id_colorMaker.setAlgorithm(currentIndex);
                }
            }

            Button {
                id: id_btnStart
                text: qsTr("Start")
                onClicked: {
                    id_colorMaker.start();
                }
            }

            Button {
                text: qsTr("Stop")
                onClicked: {
                    id_colorMaker.stop();
                }
            }
        }
    }
}
