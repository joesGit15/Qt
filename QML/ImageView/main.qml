import QtQuick 2.7
import QtQuick.Window 2.0

import QtQuick.Controls 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import QtQuick.Dialogs 1.1
import Qt.labs.settings 1.0

import Qt.User.FileOperator 1.0

ApplicationWindow {
    id: id_window

    readonly property real percent: 0.6

    visible: true;

    width: Screen.width*percent;
    height: Screen.height*percent;

    title: qsTr("Image View");

    Settings {
        id: id_settings
        property url lastpath:""

        Component.onCompleted: {
            /*
              only use these value.
            Qt.application.name = "ImageView";
            Qt.application.organization = "WT Group";
            Qt.application.domain = "WT.com";
            */
        }
    }

    Component.onCompleted: {
        id_window.x = (Screen.width - id_window.width)/2;
        id_window.y = (Screen.height - id_window.height)/2;

        if(id_settings.lastpath != ""){
            var urls = [id_settings.lastpath];
            fileDlg.updateListModel(urls);
        }
    }

    Component.onDestruction: {
        if(id_datamodel.count > 0){
            var url = id_datamodel.get(0).filepath;
            id_settings.lastpath = url;
        }
    }

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
                shortcut: "PgUp"
                onTriggered: {
                    var idx = id_listView.currentIndex;
                    if(idx-1 >= 0 && id_listView.count > 0){
                        id_listView.currentIndex = idx-1;
                    }
                }
            }
            MenuItem {
                text: qsTr("Next")
                shortcut: "PgDown"
                onTriggered: {
                    var idx = id_listView.currentIndex;
                    if(idx+1 < id_listView.count){
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

            MenuSeparator{}

            MenuItem {
                text: qsTr("Move right")
                shortcut: "Right"
                onTriggered: {
                    id_hbar.increase();
                }
            }

            MenuItem {
                text: qsTr("Move left")
                shortcut: "Left"
                onTriggered: {
                    id_hbar.decrease();
                }
            }

            MenuItem {
                text: qsTr("Move up")
                shortcut: "Up"
                onTriggered: {
                    id_vbar.decrease();
                }
            }

            MenuItem {
                text: qsTr("Move down")
                shortcut: "Down"
                onTriggered: {
                    id_vbar.increase();
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

                    /** forbidden left and right keys */
                    Keys.onLeftPressed: {}
                    Keys.onRightPressed: {}
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
                focus: true
                anchors.fill: parent
                model: id_datamodel
                delegate: id_itemdelegate
                orientation: ListView.Horizontal

                highlight: id_highlight
                highlightFollowsCurrentItem: true
                ScrollBar.horizontal: ScrollBar {}
                onCurrentIndexChanged: {
                    var idx = id_listView.currentIndex;
                    var itm = id_datamodel.get(idx);
                    if(typeof(itm) === "undefined"){
                        return;
                    }

                    if(fileOperator.isDir(itm.filepath)){
                        id_img.source = "";
                    }else{
                        id_img.source = itm.filepath;
                    }
                }
            }
        }
        Rectangle {
            id: id_imgView
            clip: true
            color: "#38373c"
            width: parent.width
            height: parent.height - id_list.height

            Flickable {
                anchors.fill: parent


                Image {
                    id: id_img
                    source: ""

                    function calXY(viewLen,imgLen){
                        var val = (viewLen - imgLen)/2;
                        if(val < 0){
                            return 0;
                        }else{
                            return val;
                        }
                    }
                    x: calXY(id_imgView.width,id_img.width)
                    y: calXY(id_imgView.height,id_img.height)
                }

                contentWidth: id_img.width
                contentHeight: id_img.height

                ScrollBar.vertical: ScrollBar {
                    id: id_vbar
                    stepSize: 0.02
                }

                ScrollBar.horizontal: ScrollBar {
                    id: id_hbar
                    stepSize: 0.02
                }

                /// why at here not to get key event
                //Keys.onUpPressed: id_vbar.decrease();
                //Keys.onDownPressed: id_vbar.increase();
                //Keys.onLeftPressed: console.log("img left");
            }
        }
    }
}

/*
        Rectangle {
            id: id_imgView
            clip: true
            //focus: true
            width: parent.width
            height: parent.height - id_list.height
            color: "#38373c"

            Keys.onUpPressed: {
                //id_vbar.decrease();
            }

            Keys.onDownPressed: {
                console.log("-----");
                //id_vbar.increase();
            }

            Image {
                id: id_img
                source: ""
                onStatusChanged: {
                    if(id_img.status == Image.Ready){
                        var S = id_img.sourceSize;
                        var x = (id_imgView.width -S.width)/2;
                        var y = (id_imgView.height-S.height)/2;

                        var barSize;
                        if(x < 0){
                            x = 0;
                            barSize = id_imgView.width/S.width;
                        }else{
                            barSize = 0.0;// has problem
                        }
                        id_hbar.setSize(barSize);

                        if(y < 0){
                            y = 0;
                            barSize = id_imgView.height/S.height;
                        }else{
                            barSize = 1.0;
                        }
                        id_vbar.setSize(barSize);

                        id_img.x = x;
                        id_img.y = y;
                    }
                }
            }

            ScrollBar {
                id: id_vbar
                stepSize: 0.01
                hoverEnabled: true
                active: hovered || pressed
                orientation: Qt.Vertical
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                onPositionChanged: {
                    var imgS = id_img.sourceSize;
                    id_img.y = -position*imgS.height;
                }
            }

            ScrollBar {
                id: id_hbar
                hoverEnabled: true
                active: hovered || pressed
                orientation: Qt.Horizontal
                size:id_img.sourceSize.width/parent.width
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                onPositionChanged: {
                    //var imgS = id_img.sourceSize;
                    //id_img.x = -position*imgS.width;
                }
            }
        }
  */

/*
        ScrollView {
            id: id_imgView
            width: parent.width
            height: parent.height - id_list.height
            horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
            verticalScrollBarPolicy: Qt.ScrollBarAsNeeded

            style: ScrollViewStyle {
                frame: Rectangle{
                    color: "#38373c"
                }
            }

            Keys.onUpPressed: {
            }
            Keys.onDownPressed: {
            }

            Image {
                id: id_img
                x:10;y:10;
                source: ""
                onStatusChanged: {
                    if(id_img.status == Image.Ready){
                        var S = id_img.sourceSize;
                        var x = (id_imgView.width -S.width)/2;
                        var y = (id_imgView.height-S.height)/2;
                        if(x < 0)x = 0;
                        if(y < 0)y = 0;
                        id_img.x = x;
                        id_img.y = y;
                    }
                }
            }
        }
        */
