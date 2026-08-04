import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Dialog {
    id: root
    width: 400
    modal: true

    // Căn giữa màn hình
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    // Bỏ tiêu đề và nút mặc định
    title: ""
    standardButtons: Dialog.NoButton

    background: Rectangle {
        color: "#1B1E42"
        radius: 20
        border.color: "#12FFFFFF"
    }

    property int loaiMucTieu: 0

    contentItem: ColumnLayout {
        spacing: 20

        // Tiêu đề tự vẽ
        Text {
            text: "Thêm mục tiêu mới"
            color: "#F4F5FC"
            font.pixelSize: 18
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 10
        }

        // ================= 1. THANH GẠT (TOGGLE BAR) =================
        Rectangle {
            Layout.fillWidth: true
            height: 44
            radius: 12
            color: "#0D111F"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 4
                spacing: 4

                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true; radius: 10
                    color: loaiMucTieu === 0 ? "#35DDC0" : "transparent"
                    Text {
                        anchors.centerIn: parent; text: "Ngắn hạn"
                        color: loaiMucTieu === 0 ? "#0D111F" : "#8A8FC0"
                        font.pixelSize: 14; font.bold: true
                    }
                    MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: loaiMucTieu = 0 }
                }

                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true; radius: 10
                    color: loaiMucTieu === 1 ? "#35DDC0" : "transparent"
                    Text {
                        anchors.centerIn: parent; text: "Dài hạn"
                        color: loaiMucTieu === 1 ? "#0D111F" : "#8A8FC0"
                        font.pixelSize: 14; font.bold: true
                    }
                    MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: loaiMucTieu = 1 }
                }
            }
        }

        // ================= 2. KHU VỰC NHẬP LIỆU =================
        StackLayout {
            Layout.fillWidth: true
            currentIndex: loaiMucTieu

            // --- TAB 0: NGẮN HẠN ---
            ColumnLayout {
                spacing: 16
                TextField { id: txtTenNganHan; placeholderText: "Tên mục tiêu"; Layout.fillWidth: true }
                ColumnLayout {
                    spacing: 8
                    Text { text: "Số tiền cần tiết kiệm"; color: "#35DDC0"; font.pixelSize: 13; font.bold: true }
                    SpinBox { id: spinSoTienNganHan; from: 0; to: 999999999; editable: true; Layout.fillWidth: true }
                }
                ColumnLayout {
                    spacing: 8
                    Text { text: "Số tháng tiết kiệm"; color: "#35DDC0"; font.pixelSize: 13; font.bold: true }
                    SpinBox { id: spinThoiHan; from: 1; to: 12; editable: true; Layout.fillWidth: true }
                }
            }

            // --- TAB 1: DÀI HẠN ---
            ColumnLayout {
                spacing: 16
                TextField { id: txtTenDaiHan; placeholderText: "Tên mục tiêu"; Layout.fillWidth: true }
                ColumnLayout {
                    spacing: 8
                    Text { text: "Số tiền cần tiết kiệm"; color: "#35DDC0"; font.pixelSize: 13; font.bold: true }
                    SpinBox { id: spinSoTienDaiHan; from: 0; to: 999999999; editable: true; Layout.fillWidth: true }
                }
                ColumnLayout {
                    spacing: 8
                    Text { text: "Số tháng tiết kiệm"; color: "#35DDC0"; font.pixelSize: 13; font.bold: true }
                    SpinBox { id: spinSoKy; from: 1; to: 360; editable: true; Layout.fillWidth: true }
                }
            }
        }

        // ================= 3. HÀNG NÚT HỦY / THÊM TỰ LÀM =================
        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 10
            spacing: 16

            Rectangle {
                Layout.fillWidth: true
                height: 40
                radius: 10
                color: "#26F2508C"
                Text { anchors.centerIn: parent; text: "Hủy"; color: "#F2508C"; font.bold: true }
                MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: root.reject() }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 40
                radius: 10
                color: "#35DDC0"
                Text { anchors.centerIn: parent; text: "Thêm"; color: "#0D111F"; font.bold: true }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if (loaiMucTieu === 0) {
                            appController.mucTieu.themNganHan(txtTenNganHan.text, spinSoTienNganHan.value, spinThoiHan.value)
                        } else {
                            appController.mucTieu.themDaiHan(txtTenDaiHan.text, spinSoTienDaiHan.value, spinSoKy.value)
                        }
                        root.accept()
                    }
                }
            }
        }
    }
}