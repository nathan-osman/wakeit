import QtQuick 2.0
import QtQuick.LocalStorage 2.0
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Ubuntu.Components.Popups 1.0
import WakeIt 1.0

MainView {
    objectName: "mainView"
    applicationName: "wakeit.nathan-osman"
    automaticOrientation: true
    useDeprecatedToolbar: false

    width: units.gu(40)
    height: units.gu(60)

    DeviceModel {
        id: deviceModel
        onError: {
            errorMessage.text = message;
            errorDialog.show();
        }
    }

    Component.onCompleted: {
        deviceModel.load();
    }

    Component {
        id: deviceDelegate

        ListItem.Empty {
            id: grid
            confirmRemoval: true
            removable: true
            width: parent.width
            onItemRemoved: {
                deviceModel.remove(index);
                deviceModel.save();
            }

            Image {
                id: deviceImage
                anchors {
                    bottom: parent.bottom
                    bottomMargin: units.gu(1)
                    left: parent.left
                    leftMargin: units.gu(1)
                    top: parent.top
                    topMargin: units.gu(1)
                }
                fillMode: Image.PreserveAspectFit
                smooth: true
                source: "graphics/device.svg"
            }

            Text {
                id: deviceTitle
                anchors {
                    left: deviceImage.right
                    leftMargin: units.gu(1)
                    right: deviceWake.left
                    rightMargin: units.gu(1)
                    top: parent.top
                    topMargin: units.gu(1)
                }
                elide: Text.ElideRight
                text: title
            }

            Text {
                id: deviceSubtitle
                anchors {
                    left: deviceImage.right
                    leftMargin: units.gu(1)
                    right: deviceWake.left
                    rightMargin: units.gu(1)
                    top: deviceTitle.bottom
                }
                elide: Text.ElideRight
                text: local ? mac : host
            }

            Button {
                id: deviceWake
                anchors {
                    bottom: parent.bottom
                    bottomMargin: units.gu(1)
                    right: parent.right
                    rightMargin: units.gu(1)
                    top: parent.top
                    topMargin: units.gu(1)
                }
                text: i18n.tr("Wake")
                visible: !busy
                onClicked: {
                    deviceModel.wake(index)
                }
            }

            ActivityIndicator {
                anchors {
                    bottom: parent.bottom
                    right: parent.right
                    rightMargin: units.gu(1)
                    top: parent.top
                }
                running: busy
            }
        }
    }

    Dialog {
        id: addDialog
        title: i18n.tr("Add Device")

        TextField {
            id: deviceTitle
            placeholderText: i18n.tr("Descriptive title")
        }

        Row {
            spacing: units.gu(1)

            CheckBox {
                id: deviceLocal
                checked: true
            }

            Label {
                text: i18n.tr("Send as broadcast packet\n(disable for WAN)")
            }
        }

        TextField {
            id: deviceHost
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            placeholderText: i18n.tr("Hostname or IP address")
            visible: !deviceLocal.checked
        }

        TextField {
            id: deviceMac
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            placeholderText: i18n.tr("MAC address")
        }

        TextField {
            id: devicePort
            inputMethodHints: Qt.ImhDigitsOnly
            placeholderText: i18n.tr("Port (typically 9)")
        }

        Row {
            spacing: units.gu(1)

            Button {
                color: UbuntuColors.orange
                text: i18n.tr("Add")
                onClicked: {

                    // Add the device and save the list
                    deviceModel.add({
                        title: deviceTitle.text,
                        local: deviceLocal.checked,
                        host: deviceHost.text,
                        mac: deviceMac.text,
                        port: devicePort.text
                    });
                    deviceModel.save();

                    // Hide the dialog and reset the inputs
                    addDialog.hide();
                    deviceTitle.text = "";
                    deviceLocal.checked = true;
                    deviceHost.text = "";
                    deviceMac.text = "";
                    devicePort.text = "";
                }
            }

            Button {
                text: i18n.tr("Cancel")
                onClicked: addDialog.hide()
            }
        }
    }

    // Shown when an error occurs
    Dialog {
        id: errorDialog
        title: i18n.tr("Error")

        Label {
            id: errorMessage
        }

        Button {
            text: i18n.tr("Close")
            onClicked: errorDialog.hide()
        }
    }

    Page {
        title: i18n.tr("Wake It!")

        // Display a helpful message indicating that there are no items
        Label {
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            text: i18n.tr("Use the toolbar to add a device")
            visible: !listView.count
        }

        ListView {
            id: listView
            anchors.fill: parent
            visible: listView.count

            // Display a list of devices that can be woken up
            model: deviceModel
            delegate: deviceDelegate
        }

        tools: ToolbarItems {
            ToolbarButton {
                action: Action {
                    iconName: "add"
                    onTriggered: addDialog.show()
                }
            }
        }
    }
}
