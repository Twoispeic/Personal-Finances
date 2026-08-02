import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root
    title: "Góp tiết kiệm"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    width: 350

    property int mucTieuId: -1
    property double soTienConDu: 0
    property string tenMucTieu: ""

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        Text { text: "Còn dư: " + root.soTienConDu.toLocaleString() + " đ"; color: "#8A90A6" }
        Text { text: "Góp cho: " + root.tenMucTieu; color: "white"; font.bold: true }

        SpinBox {
            id: spinSoTienGop
            Layout.fillWidth: true
            from: 0
            to: root.soTienConDu
            editable: true
        }
    }

    onAccepted: {
        appController.gopTietKiem(root.mucTieuId, spinSoTienGop.value)
    }
}