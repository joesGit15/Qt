import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0
import Qt.User.FileOperator 1.0

ApplicationWindow {
    property real percent: 0.6;

    visible: true;

    width: Screen.width*percent;
    height: Screen.height*percent;
    //x:(Screen.desktopAvailableWidth - width)/2;
    // the desktopAvailableHeight will two screen width
    x:(Screen.width-width)/2;
    y:(Screen.height-height)/2;

    title: qsTr("Image View");

    FileOperator{id:fileOperator}

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File");

            MenuItem {
                text: qsTr("Open Image...");
                shortcut: StandardKey.Open;
                onTriggered: {
                    fileDlg.open();
                }
            }

            MenuSeparator{}

            MenuItem {
                text: qsTr("Quit");
                shortcut: StandardKey.Quit;
                onTriggered: {
                    Qt.quit();
                }
            }
        }
    }

    FileDialog{
        id: fileDlg;
        visible: false;
        selectFolder: false
        selectMultiple: true
        folder: shortcuts.pictures;
        title: qsTr("Please select images")
        nameFilters: ["Image files (*.jpg *.png)","All files(*)"]

        onAccepted: {
            var urls = fileDlg.fileUrls;
            urls = fileOperator.getAllUrls(urls);
            for(var i=0; i < urls.length; i++){
                id_datamodel.append({"filepath":urls[i]});
            }
        }
    }

    Column {
        anchors.fill: parent;

        Rectangle {
            id:id_list
            property int itemlen: 100

            width: parent.width
            height: itemlen

            ListModel { id: id_datamodel; }
            Component{
                id: id_itemdelegate;
                Item {
                    id: id_delegate
                    width: id_list.itemlen;
                    height: id_list.itemlen;

                    Image {
                        anchors.fill: parent
                        anchors.margins: 5
                        source: {
                            var path;
                            if(fileOperator.isDir(filepath)){
                                path = "qrc:/img/imgs/directory.png";
                            }else{
                                path = filepath;
                            }
                            return path;
                        }
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter
                    }

                    MouseArea{
                        anchors.fill: parent;
                        onClicked: {
                            id_listView.currentIndex = index;
                        }
                    }
                }
            }

            Component {
                id:id_highlight;
                Rectangle {
                    width: id_list.itemlen;
                    height: id_list.itemlen;
                    color: "blue";
                    x: id_listView.currentItem.x;
                    Behavior on x{
                        SpringAnimation {
                            spring: 3;
                            damping: 0.2;
                        }
                    }
                }

            }
            ListView {
                id: id_listView
                anchors.fill: parent
                orientation: ListView.Horizontal
                model: id_datamodel
                delegate: id_itemdelegate
                focus: true

                highlight: id_highlight
                highlightFollowsCurrentItem: true
                /* Can Print which c++ class of qml object, and you can watch head file to find some things*/
                /* Component.onCompleted: { console.log(id_listView); } */
                onCurrentIndexChanged: {
                    var idx = id_listView.currentIndex;
                    var itm = id_datamodel.get(idx);
                    if(fileOperator.isDir(itm.filepath)){
                        img.source = "";
                    }else{
                        img.source = itm.filepath;
                    }
                }
            }
        }

        Rectangle {
            width: parent.width
            height: parent.height - id_list.height

            color: "#38373c"

            Image {
                id: img
                anchors.fill: parent
                //mipmap: true
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: ""
            }
        }
    }
}
