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
        spacing: 10;
        anchors.fill: parent;

        Rectangle {
            id:id_list;
            height: parent.height;
            width: parent.width;

            ListModel { id: id_datamodel; }
            Component{
                id: id_itemdelegate;
                Row {
                    spacing: 10;
                    Rectangle{
                        width: id_list.width;
                        height: 50;
                        color:"#aabbcc";

                        Text {
                            anchors.fill: parent;

                            width: parent.width;
                            height: parent.height;

                            padding: 5;

                            elide: Text.ElideMiddle;
                            //color: "#aabbcc"; // before-color
                            font.family: "Loma";

                            text: filename;
                        }
                    }
                }
            }

            ListView {
                anchors.fill: parent;
                model: id_datamodel;
                delegate: id_itemdelegate;
            }
        }

        /*
        Rectangle {
            anchors.left: list.right;
            height: parent.height;
            width: parent.width - list.width;
            //Layout.alignment: Qt.AlignRight;
            color: "#223344";
        }
        */
    }
}
