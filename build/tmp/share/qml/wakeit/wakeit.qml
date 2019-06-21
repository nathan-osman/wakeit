import QtQuick 2.0
import QtQuick.LocalStorage 2.0

import Ubuntu.Components 1.3
import Ubuntu.Components.ListItems 1.3 as ListItem
import Ubuntu.Components.Popups 1.3

import WakeIt 1.0

MainView {
    objectName: "mainView"
    applicationName: "wakeit.nathan-osman"
    automaticOrientation: true
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
            onPressAndHold: {
                editDialog.deviceTitle = deviceModel.title(index)
                editDialog.deviceLocal = deviceModel.local(index)
                editDialog.deviceHost = deviceModel.host(index)
                editDialog.deviceMac = deviceModel.mac(index)
                editDialog.devicePort = deviceModel.port(index)
                editDialog.index = index
                editDialog.show()
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
                source: "../../../graphics/device.svg"
            }

            Text {
                id: deviceTitle
                color: Theme.palette.normal.foregroundText
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
                color: Theme.palette.normal.foregroundText
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
                color: UbuntuColors.green
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

    ModifyDialog {
        id: editDialog
        title: i18n.tr("Edit Device")
        ackText: i18n.tr("Apply")

        onAcknowledged: {
            // update device and save the list
            deviceModel.update(index, {
               title: deviceTitle,
               local: deviceLocal,
               host: deviceHost,
               mac: deviceMac,
               port: devicePort
            });
            deviceModel.save()
            editDialog.hide()
        }
    }

    ModifyDialog {
        id: addDialog
        title: i18n.tr("Add Device")
        ackText: i18n.tr("Add")

        onAcknowledged: {
            // Add the device and save the list
            deviceModel.add({
                title: deviceTitle,
                local: deviceLocal,
                host: deviceHost,
                mac: deviceMac,
                port: devicePort
            });
            deviceModel.save();

            // Hide the dialog and reset the inputs
            addDialog.hide();
            deviceTitle = "";
            deviceLocal = true;
            deviceHost = "";
            deviceMac = "";
            devicePort = "";
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
           header: PageHeader {

                id: pageHeader
                title: i18n.tr("Wake It!")
                StyleHints {
                    foregroundColor: "white"
                    backgroundColor: "#42A1DD"
                    dividerColor: UbuntuColors.silk
                }
                trailingActionBar {
                    actions: [
                        Action {
                            iconName: "add"
                            text: i18n.tr("Add")
                            onTriggered: addDialog.show()

                        }
                   ]
                   numberOfSlots: 1
                }
            }
           
        

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
            anchors.top: pageHeader.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            visible: listView.count

            // Display a list of devices that can be woken up
            model: deviceModel
            delegate: deviceDelegate
        }

       
         
    }
}
