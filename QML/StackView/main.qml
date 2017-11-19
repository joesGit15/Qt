import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

ApplicationWindow {
    readonly property real percent: 0.6;

    visible: true
    title: qsTr("Stack View")

    width: Screen.width*percent;
    height: Screen.height*percent;
    x:(Screen.width-width)/2;
    y:(Screen.height-height)/2;

    Component {
        id: id_sViewItem
        Row {
            spacing: 10
            Button {
                text: qsTr("Push")
                onClicked: id_stack.push(id_sViewItem)
            }

            Button {
                text: qsTr("Pop")
                enabled: id_stack.depth > 1
                onClicked: id_stack.pop()
            }

            Text {
                text: id_stack.depth
            }
        }
    }

    StackView {
        id: id_stack

        anchors.fill: parent
        initialItem: id_sViewItem
        onCurrentItemChanged: {
            console.log("item Changed :" + id_stack.depth);
        }
    }
}
