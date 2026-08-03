import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root
    title: "Thêm chi tiêu"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    width: 350

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        Text { text: "Loại chi tiêu:"; color: "white" }

        ComboBox {
            id: comboLoai
            Layout.fillWidth: true
            // Lấy danh sách phân loại từ C++ (AppController)
            model: appController.chiTieu.danhSachPhanLoai
            textRole: "text"
        }

        Text { text: "Số tiền:"; color: "white" }

        SpinBox {
            id: spinSoTien
            Layout.fillWidth: true
            from: 0
            to: 999999999
            editable: true
        }
    }

    onAccepted: {
        var loaiValue = appController.chiTieu.danhSachPhanLoai[comboLoai.currentIndex].value
        appController.chiTieu.them(loaiValue, spinSoTien.value)
    }
}