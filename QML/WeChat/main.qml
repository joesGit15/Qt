import QtQuick 2.6
import QtQuick.Controls 1.4 as Old
import QtQuick.Controls 2.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("WeChat")

    header: ToolBar {
        height: 50

        Rectangle {
            property int nHMargin: 15

            anchors.fill: parent
            color: "black"

            Label {
                x:parent.nHMargin;
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("WeChat")
                color: "white"
                font.bold: true
                font.pointSize: 14
            }

            Old.ToolButton {
                anchors.right: idAddBtn.left
                anchors.rightMargin: parent.nHMargin
                anchors.verticalCenter: parent.verticalCenter
                iconName: qsTr("Search")
                iconSource: "qrc:/imgs/search.png"
                onClicked: {console.log("Search btn clicked");}
            }

            Old.ToolButton {
                id: idAddBtn
                anchors.right: parent.right
                anchors.rightMargin: parent.nHMargin
                anchors.verticalCenter: parent.verticalCenter
                iconName: qsTr("Add")
                iconSource: "qrc:/imgs/add.png"
                onClicked: {console.log("Add btn clicked");}
            }
        }
    }

    footer: TabBar {
        id: bar
        width: parent.width
        background: Rectangle {
            color: "#eeeeee"
        }

        TabButton {
            text: qsTr("Home")
        }
        TabButton {
            text: qsTr("Discover")
        }
        TabButton {
            text: qsTr("Activity")
        }
        TabButton {
            text: qsTr("School")
        }
    }
}
