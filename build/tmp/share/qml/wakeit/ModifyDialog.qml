import QtQuick 2.9

import Ubuntu.Components 1.3
import Ubuntu.Components.Popups 1.3

Dialog {
    id: modifyDialog
    property alias ackText: ackButton.text
    property alias deviceTitle: deviceTitle.text
    property alias deviceLocal: deviceLocal.checked
    property alias deviceHost: deviceHost.text
    property alias deviceMac: deviceMac.text
    property alias devicePort: devicePort.text
    property int index
    signal acknowledged

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
            text: i18n.tr("Cancel")
            onClicked: modifyDialog.hide()
        }
        Button {
            id: ackButton
            color: UbuntuColors.green
            onClicked: modifyDialog.acknowledged()
        }

      
    }
}
