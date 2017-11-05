import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0

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
        /*
        title: qsTr("Please choose a file");
        nameFilters: ["Image files (*.jpg *.png)","All files(*)"]
        selectFolder: false;
        selectMultiple: true;
        */

        onAccepted: {
            if(fileDlg.selectFolder){
                console.log("open folder" + fileDlg.folder);
            }else{
                var urls = fileDlg.fileUrls;
                for(var i=0; i < urls.length; i++){
                    datamodel.append({"filepath": urls[i]});
                }
            }
        }

        /*
        Component.onCompleted: {
            visible = true;
        }
        */
    }

/*
    ListModel {
        id: datamodel;

        ListElement {
            filepath: ""
        }
    }

    ListView{
        width: 100;
        height: 200;
        model: datamodel;
        delegate: Text {
            text: filepath;
        }
    }
*/
    Rectangle{
        width: 200;
        height: 200;

        ListModel {
            id: datamodel;
        }

        Component{
            id: itemdelegate;
            Row {
                spacing: 10;
                Text {
                    text: filepath;
                }
            }
        }

        ListView {
            anchors.fill: parent;
            model: datamodel;
            delegate: itemdelegate;
        }
    }
}
