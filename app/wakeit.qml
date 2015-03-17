import QtQuick 2.0
import QtQuick.LocalStorage 2.0

import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Ubuntu.Components.Popups 1.0

import Wakeit 1.0

MainView {
    objectName: "mainView"
    applicationName: "wakeit.nathan-osman"
    automaticOrientation: true
    useDeprecatedToolbar: false

    width: units.gu(40)
    height: units.gu(60)

    // Database used for storing devices
    property var db

    // Create the database if it does not exist when initializing
    Component.onCompleted: {
        db = LocalStorage.openDatabaseSync('WakeIt', '1.0', 'Wake It! Database', 10, function(db) {
            db.transaction(function(tx) {
                tx.executeSql('CREATE TABLE Device(host TEXT, mac TEXT)');
            });
            db.changeVersion('', '1.0');
        });
        reload();
    }

    // Reload the devices from the database
    function reload() {
        db.transaction(function(tx) {
            deviceModel.clear();
            var rs = tx.executeSql('SELECT host, mac FROM Device ORDER BY host');
            for(var i = 0; i < rs.rows.length; ++i) {
                deviceModel.append(rs.rows.item(i));
            }
        });
    }

    // Dialog for adding devices
    Dialog {
        id: addDialog
        title: i18n.tr("Add Device")

        TextField {
            id: host
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            placeholderText: i18n.tr("Hostname or IP address")
        }

        TextField {
            id: mac
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            placeholderText: i18n.tr("MAC address (eg. xx:xx...)")
        }

        Button {
            text: i18n.tr("Add")
            color: UbuntuColors.orange
            onClicked: {
                db.transaction(function(tx) {
                    tx.executeSql('INSERT INTO Device VALUES(?, ?)', [host.text, mac.text]);
                });
                addDialog.hide();
                host.text = '';
                mac.text = '';
                reload();
            }
        }

        Button {
            text: i18n.tr("Cancel")
            onClicked: addDialog.hide()
        }
    }

    // Whether the packet sending operation is in progress or not
    property bool inProgress: false

    // Dialog shown when:
    // - packets are being sent
    // - an error of some sort occurred
    // - packets are finished being sent
    Dialog {
        id: sendDialog
        title: i18n.tr("Sending Packets")

        ActivityIndicator {
            running: inProgress
            visible: inProgress
        }

        Text {
            horizontalAlignment: Text.AlignHCenter
            id: dialogText
            visible: !inProgress
        }

        // Custom C++ component for sending packets
        UdpSocket {
            id: socket

            onCompleted: sendDialog.hide()
            onError: {
                inProgress = false;
                dialogText.text = message;
            }
        }

        function showDialog(host, mac) {
            inProgress = true;
            show();
            socket.sendPackets(host, mac);
        }

        Button {
            text: i18n.tr("Cancel")
            visible: inProgress
            onClicked: {
                socket.cancel();
                sendDialog.hide();
            }
        }

        Button {
            text: i18n.tr("Close")
            visible: !inProgress
            onClicked: sendDialog.hide()
        }
    }

    Page {
        title: i18n.tr("Wake It!")

        // Display a helpful message indicating that there are no items
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: i18n.tr("Use the toolbar to add a device")
            visible: !deviceModel.count
        }

        ListView {
            anchors.fill: parent
            visible: deviceModel.count

            // Display a list of devices that can be woken up
            model: ListModel { id: deviceModel }
            delegate: ListItem.Subtitled {
                text: host
                subText: mac
                onTriggered: sendDialog.showDialog(host, mac)
            }
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
