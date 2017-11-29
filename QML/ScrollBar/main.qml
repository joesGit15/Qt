import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    visible: true
    width: 640
    height: 480


    Flickable {
        anchors.fill: parent
        focus: true

        Rectangle {
            id:id_rect
            width: 800
            height: 800
            rotation: 45

            gradient: Gradient {
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 0.2; color: "red" }
                GradientStop { position: 0.3; color: "yellow" }
                GradientStop { position: 0.6; color: "green" }
                GradientStop { position: 0.7; color: "blue" }
                GradientStop { position: 1.0; color: "white" }
            }
        }

        contentWidth: id_rect.width
        contentHeight: id_rect.height

        ScrollBar.horizontal: ScrollBar {
            id: id_hbar
            stepSize: 0.01
            active: id_vbar.active
        }

        ScrollBar.vertical: ScrollBar {
            id: id_vbar
            stepSize: 0.01
            active: id_hbar.active
        }

        Keys.onUpPressed: {
            id_vbar.decrease();
        }
        Keys.onDownPressed: {
            id_vbar.increase();
        }
        Keys.onLeftPressed: {
            id_hbar.decrease();
        }
        Keys.onRightPressed: {
            id_hbar.increase();
        }
    }
}
