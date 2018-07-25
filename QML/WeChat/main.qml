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
                width: parent.height - 4
                height: parent.height - 4
                anchors.right: idTBtnAdd.left
                anchors.rightMargin: parent.nHMargin
                anchors.verticalCenter: parent.verticalCenter
                iconName: qsTr("Search")
                iconSource: "qrc:/imgs/search.png"
                onClicked: {console.log("Search btn clicked");}
            }

            Old.ToolButton {
                id: idTBtnAdd
                width: parent.height - 4
                height: parent.height - 4
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
        width: parent.width

        background: Rectangle {
            color: "#eeeeee"
        }

        Button {
            id: idTBtnWeChat
            //text: qsTr("WeChat")

            background: Rectangle {
                anchors.fill: parent
                //border.color: idTBtnWeChat.down ? "#17a81a" : "#21be2b"
            }
        }

        Button {
            id: idBtnContacts
        }
    }
}
