import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Dialog {
    id: root
    title: "Thêm mục tiêu mới"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    width: 400

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            TabButton { text: "Ngắn hạn" }
            TabButton { text: "Dài hạn" }
        }

        StackLayout {
            currentIndex: tabBar.currentIndex
            Layout.fillWidth: true

            // Tab Ngắn hạn
            ColumnLayout {
                spacing: 8
                TextField { id: txtTenNganHan; placeholderText: "Tên mục tiêu"; Layout.fillWidth: true }
                SpinBox { id: spinSoTienNganHan; from: 0; to: 999999999; editable: true; Layout.fillWidth: true }
                SpinBox { id: spinThoiHan; from: 1; to: 12; editable: true; Layout.fillWidth: true }
            }

            // Tab Dài hạn
            ColumnLayout {
                spacing: 8
                TextField { id: txtTenDaiHan; placeholderText: "Tên mục tiêu"; Layout.fillWidth: true }
                SpinBox { id: spinSoTienDaiHan; from: 0; to: 999999999; editable: true; Layout.fillWidth: true }
                SpinBox { id: spinSoKy; from: 1; to: 360; editable: true; Layout.fillWidth: true }
            }
        }
    }

    onAccepted: {
        if (tabBar.currentIndex === 0) {
            appController.themMucTieuNganHan(txtTenNganHan.text, spinSoTienNganHan.value, spinThoiHan.value)
        } else {
            appController.themMucTieuDaiHan(txtTenDaiHan.text, spinSoTienDaiHan.value, spinSoKy.value)
        }
    }
}