import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

ApplicationWindow {
    property int nToolHeight: 50

    id: idApp
    visible: true
    width: 640
    height: 480
    title: qsTr("WeChat")

    header: ToolBar {
        height: idApp.nToolHeight

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

            ToolButton {
                id: idBtnSearch
                height: parent.height
                width:  parent.height
                anchors.right: idBtnAdd.left
                //anchors.rightMargin: parent.nHMargin
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {console.log("Search btn clicked");}

                contentItem: Image {
                    source: "qrc:/imgs/search.png"
                }
            }

            ToolButton {
                id: idBtnAdd
                width: parent.height
                height: parent.height
                anchors.right: parent.right
                anchors.rightMargin: parent.nHMargin
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {console.log("Add btn clicked");}

                contentItem: Image {
                    source: "qrc:/imgs/add.png"
                }
            }
        }
    }

    footer: TabBar {
        height: idApp.nToolHeight

        background: Rectangle {
            color: "#eeeeee"
        }

        TabButton {
            //width: parent.height
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            contentItem: Image {
                fillMode: Image.PreserveAspectFit
                source: "qrc:/imgs/wechat_active.png"
            }
        }
        TabButton { text: qsTr("Discover") }
        TabButton { text: qsTr("Activity") }
    }
}
