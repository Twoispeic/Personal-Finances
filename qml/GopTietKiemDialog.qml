import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Dialog {
    id: root
    title: "Nộp tiền tiết kiệm"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    width: 350
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    property int mucTieuId: -1
    property string tenMucTieu: ""
    property double soTienConDu: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 12
        Text { text: "Góp cho: " + root.tenMucTieu; color: "#F4F5FC"; font.bold: true }
        Text {
            text: "Số dư khả dụng: " + root.soTienConDu.toLocaleString('vi-VN') + " đ"
            color: "#8A8FC0"; font.pixelSize: 12
        }
        SpinBox {
            id: spinSoTienGop
            Layout.fillWidth: true
            from: 0
            to: root.soTienConDu > 0 ? root.soTienConDu : 999999999
            editable: true
        }
    }

    onAccepted: {
        appController.mucTieu.gop(root.mucTieuId, spinSoTienGop.value)
    }
}