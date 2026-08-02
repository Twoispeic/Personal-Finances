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
    property var danhSachLoai: [
        { text: "Tiền sinh hoạt", value: 0 },
        { text: "Tiền điện nước", value: 1 },
        { text: "Tiền nhà", value: 2 },
        { text: "Khác", value: 3 }
    ]

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        Text { text: "Loại chi tiêu:"; color: "white" }
        ComboBox {
            id: comboLoai
            Layout.fillWidth: true
            model: root.danhSachLoai
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
        appController.chiTieu.them(danhSachLoai[comboLoai.currentIndex].value, spinSoTien.value)
    }
}