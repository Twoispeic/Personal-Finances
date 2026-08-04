import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Dialog {
    id: root
    property int mucTieuId: -1
    property string tenMucTieu: ""
    property real soTienDaTietKiem: 0

    title: "Xác nhận hoàn thành mục tiêu"
    modal: true
    standardButtons: Dialog.Yes | Dialog.No
    width: 400

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        Text {
            text: "Xác nhận mục tiêu \"" + tenMucTieu + "\" đã hoàn thành?"
            color: "#F4F5FC"
            font.bold: true
            font.pixelSize: 15
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Text {
            text: "Mục tiêu sẽ bị xoá khỏi danh sách. " + soTienDaTietKiem.toLocaleString('vi-VN')
                + " đ đã tiết kiệm cho mục tiêu này sẽ KHÔNG được trả lại vào hũ tiết kiệm khả dụng "
                + "(coi như đã dùng đúng mục đích). Hành động này không thể hoàn tác."
            color: "#8A8FC0"
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }
    }

    onAccepted: {
        appController.hoanThanhMucTieu(mucTieuId)
    }
}