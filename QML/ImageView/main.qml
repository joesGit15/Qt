import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1
import Qt.User.FileOperator 1.0

ApplicationWindow {
    readonly property real percent: 0.6;

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
            title: qsTr("&File")

            MenuItem {
                text: qsTr("Open Image...")
                shortcut: StandardKey.Open
                onTriggered: {
                    fileDlg.open();
                }
            }

            MenuSeparator{}

            MessageDialog {
                id:id_removeMsgDlg
                title: qsTr("Remove Information Dialog")
                icon: StandardIcon.Question
                text: qsTr("Are you sure to remove current image?")
                standardButtons: StandardButton.Cancel | StandardButton.Ok
                visible: false
                onAccepted: {
                    var idx = id_listView.currentIndex;
                    if(idx >=0 && idx < id_listView.count){
                        var path = id_datamodel.get(idx).filepath;
                        fileOperator.removefile(path);
                        id_datamodel.remove(idx);
                        id_listView.currentIndexChanged(idx);
                    }
                }
            }

            MenuItem {
                text: qsTr("Remove Current")
                shortcut: StandardKey.Delete
                onTriggered:{
                    var idx = id_listView.currentIndex;
                    var path = id_datamodel.get(idx).filepath;
                    if(!fileOperator.isDir(path)){
                        id_removeMsgDlg.open();
                    }
                }
            }

            MenuSeparator{}

            MenuItem {
                text: qsTr("Quit")
                shortcut: StandardKey.Quit
                onTriggered: {
                    Qt.quit();
                }
            }
        }

        Menu {
            title: qsTr("&View")

            MenuItem {
                text: qsTr("Previous")
                shortcut: "Left"
                onTriggered: {
                    var idx = id_listView.currentIndex;
                    if(idx-1 >= 0 && id_listView.count > 0){
                        id_listView.currentIndex = idx-1;
                    }
                }
            }
            MenuItem {
                text: qsTr("Next")
                shortcut: "Right"
                onTriggered: {
                    var idx = id_listView.currentIndex;
                    if(idx+1 < id_listView.count-1){
                        id_listView.currentIndex = idx+1;
                    }
                }
            }
            MenuItem {
                text: qsTr("First")
                shortcut: "Home"
                onTriggered: {
                    if(id_listView.count > 0){
                        id_listView.currentIndex = 0;
                    }
                }
            }
            MenuItem {
                text: qsTr("Last")
                shortcut: "End"
                onTriggered: {
                    var count = id_listView.count;
                    if(count > 0){
                        id_listView.currentIndex = count-1;
                    }
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

        function updateListModel(urls){
            urls = fileOperator.getAllUrls(urls);
            id_datamodel.clear();
            var path,i;
            for(i=0; i < urls.length; i++){
                path = urls[i];
                id_datamodel.append({"filepath":path});
            }

            var currentidx = -1;
            for(i=0; i < id_datamodel.count; i++){
                path = id_datamodel.get(i).filepath;
                if(!fileOperator.isDir(path)){
                    currentidx = i;
                    break;
                }
            }

            if(-1 === currentidx){
                currentidx = 0;
            }
            id_listView.currentIndex = currentidx;
        }

        onAccepted: {
            updateListModel(fileDlg.fileUrls);
        }
    }

    Column {
        anchors.fill: parent;

        Rectangle {
            id:id_list
            property int itemlen: 100

            width: parent.width
            height: itemlen

            ListModel {
                id: id_datamodel;
            }

            Component {
                id: id_itemdelegate;
                Item {
                    id: id_delegate
                    width: id_list.itemlen
                    height: id_list.itemlen

                    Image {
                        anchors.fill: parent
                        anchors.margins: 5
                        source: {
                            if(typeof(filepath) === "undefined"){
                                return "";
                            }

                            var path;
                            id_filename.visible = false;
                            if(0 === index){
                                path = "qrc:/img/imgs/parent_folder.png";
                            }else if(fileOperator.isDir(filepath)){
                                path = "qrc:/img/imgs/folder.png";
                                id_filename.visible = true;
                                id_filename.text = fileOperator.filename(filepath);
                            }else{
                                path = filepath;
                            }
                            return path;
                        }
                        fillMode: Image.PreserveAspectFit
                        horizontalAlignment: Image.AlignHCenter
                        verticalAlignment: Image.AlignVCenter

                        Text {
                            id: id_filename
                            anchors.centerIn: parent
                            elide: Text.ElideMiddle
                            width: parent.width-5
                            horizontalAlignment: Text.AlignHCenter
                            color: "#196cbe"
                        }
                    }

                    function changeFolder(idx){
                        var path = id_datamodel.get(idx).filepath;
                        if(fileOperator.isDir(path)){
                            fileDlg.updateListModel([path]);
                        }
                    }

                    MouseArea{
                        anchors.fill: parent;
                        onClicked: {
                            id_listView.currentIndex = index;
                        }
                        onDoubleClicked: {
                            changeFolder(index);
                        }
                    }

                    Keys.onReturnPressed: {
                        changeFolder(index);
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
                            spring: 4;
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
                    if(typeof(itm) === "undefined"){
                        return;
                    }

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
                fillMode: Image.PreserveAspectFit
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: ""
            }
        }
    }
}
