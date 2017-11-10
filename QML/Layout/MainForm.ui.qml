import QtQuick 2.5

Rectangle {


    width: 400
    height: 800

    Column {
        anchors.fill: parent
        property int itemH: parent.height/4

        Column {
            property int itemH: parent.itemH/3

            width: parent.width
            height: parent.itemH

            Rectangle {
                width: parent.width
                height: parent.itemH
                color: "#8388e5"
            }

            Rectangle {
                width: parent.width
                height: parent.itemH
                color: "#6cc5d7"
            }

            Rectangle {
                width: parent.width
                height: parent.itemH
                color: "#5cc733"
            }
        }

        Row {
            property int itemH: parent.itemH/3
            width: parent.width
            height: parent.itemH

            Rectangle {
                width: parent.width/3
                height: parent.height
                color: "#6f3ebc"
            }

            Rectangle {
                width: parent.width/3
                height: parent.height
                color: "#49d570"
            }

            Rectangle {
                width: parent.width/3
                height: parent.height
                color: "#dd4b4b"
            }
        }

        Grid {
            property int itemW: parent.width/4
            property int itemH: parent.itemH/2

            width: parent.width
            height: parent.itemH

            spacing: 0

            rows: 2
            columns: 4

            Rectangle { width: parent.itemW; height: parent.itemH; color: "#1dd95f" }
            Rectangle { width: parent.itemW; height: parent.itemH; color: "#3e73d3" }
            Rectangle { width: parent.itemW; height: parent.itemH; color: "#811dab" }
            Rectangle { width: parent.itemW; height: parent.itemH; color: "#3e73d3" }

            Rectangle { width: parent.itemW; height: parent.itemH; color: "#c29ad3" }
            Rectangle { width: parent.itemW; height: parent.itemH; color: "#811dab" }
            Rectangle { width: parent.itemW; height: parent.itemH; color: "#3e73d3" }
            Rectangle { width: parent.itemW; height: parent.itemH; color: "#1dd95f" }
        }

        Flow {
            property int itemLen: 50

            width: parent.width
            height: parent.itemH
            spacing: 2

            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#1dd95f" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#3e73d3" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#811dab" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#e2b41d" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#5392d0" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#17599a" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#b69edd" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#8ae79a" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#9a4a82" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#eeee5f" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#106bc6" }
            Rectangle { width: parent.itemLen; height: parent.itemLen; color: "#7f55d8" }

        }
    }
}
