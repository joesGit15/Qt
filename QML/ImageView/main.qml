import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    property real percent: 0.6;

    visible: true;

    width: Screen.width*percent;
    height: Screen.height*percent;
    //x:(Screen.desktopAvailableWidth - width)/2;
    // the desktopAvailableHeight will two screen width
    x:(Screen.width-width)/2;
    y:(Screen.height-height)/2;

    color: "#AABBCC";
    title: qsTr("Hello World");

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File");

            MenuItem {
                text: qsTr("Open Image...");
                shortcut: StandardKey.Open;
                onTriggered: {
                    fileDlg.setTitle(qsTr("Please select images"));
                    fileDlg.setNameFilters(["Image files (*.jpg *.png)","All files(*)"]);
                    fileDlg.setSelectMultiple(true);
                    fileDlg.setSelectFolder(false);
                    fileDlg.open();
                }
            }

            MenuItem {
                text: qsTr("Open Directory...");
                shortcut: "Ctrl+Shift+O";
                onTriggered: {
                    fileDlg.setTitle(qsTr("Please select image folder"));
                    fileDlg.setSelectMultiple(false);
                    fileDlg.setSelectFolder(true);
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
        folder: shortcuts.pictures;

        onAccepted: {
            if(fileDlg.selectFolder){
                console.log("open folder" + fileDlg.folder);
            }else{
                var filepath,idx,filename;
                var urls = fileDlg.fileUrls;
                for(var i=0; i < urls.length; i++){
                    filepath = urls[i].toString();
                    if(-1 !== filepath.indexOf('/')){
                        idx = filepath.lastIndexOf('/');
                    }else{
                        idx = filepath.lastIndexOf('\\');
                    }

                    filename = filepath.substr(idx+1);
                    id_datamodel.append({"filename": filename});
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent;

        Rectangle {
            id:id_list;

            property int itemH: 30;

            height: parent.height;
            width: 250;

            ListModel { id: id_datamodel; }

            Component{
                id: id_itemdelegate;
                Item {
                    width: id_list.width;
                    height: id_list.itemH;

                    Text {
                        anchors.fill: parent;

                        padding: 5;

                        elide: Text.ElideMiddle;
                        font.family: "Loma";

                        text: filename;
                    }
                }
            }

            Component {
                id:id_highlight;
                Rectangle {
                    width: id_list.width;
                    height: id_list.itemH;
                    color: "lightblue";
                    y: id_listView.currentItem.y;
                    Behavior on y{
                        SpringAnimation {
                            spring: 3;
                            damping: 0.2;
                        }
                    }
                }
            }

            ListView {
                id: id_listView;
                anchors.fill: parent;
                model: id_datamodel;
                delegate: id_itemdelegate;
                focus: true;

                highlight: id_highlight;
                highlightFollowsCurrentItem: false;
            }
        }

        /*
        Rectangle {
            anchors.left: id_list.right;
            height: parent.height;
            width: parent.width - id_list.width;
            color: "#223344";
        }
        */
    }
}
