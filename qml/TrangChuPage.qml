import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    // --- LỚP 1: CỐ ĐỊNH KÍCH THƯỚC TRANG VỚI STACKVIEW ---
    anchors.fill: parent

    // --- LỚP 2: TẠO PADDING SO VỚI VIỀN (Đúng chuẩn mockup) ---
    Item {
        anchors.fill: parent
        anchors.margins: 40

        ColumnLayout {
            anchors.fill: parent
            spacing: 28

            // ================= 1. TOPBAR =================
            RowLayout {
                Layout.fillWidth: true

                ColumnLayout {
                    spacing: 4
                    Text {
                        text: "Chào " + (appController.tenNguoiDung !== "" ? appController.tenNguoiDung : "bạn") + ", cùng tiết kiệm nhé 👋"
                        color: "#F4F5FC"
                        font.pixelSize: 26
                        font.bold: true
                    }
                    Text {
                        text: "Đây là tình hình tài chính của bạn trong tháng này"
                        color: "#8A8FC0"
                        font.pixelSize: 14
                    }
                }

                Item { Layout.fillWidth: true }

                Rectangle {
                        width: 150; height: 36; radius: 18
                        color: "#35DDC0"
                        Text {
                            anchors.centerIn: parent
                            text: "Chốt sổ tháng này"
                            color: "#0D111F"; font.pixelSize: 12; font.bold: true
                        }
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: xacNhanChotSoDialog.open()
                        }
                    }

                Rectangle {
                    width: 44; height: 44; radius: 22
                    color: "#F2508C"
                    Text {
                        anchors.centerIn: parent
                        text: appController.tenNguoiDung !== "" ? appController.tenNguoiDung.charAt(0).toUpperCase() : "U"
                        color: "#F4F5FC"
                        font.pixelSize: 18
                        font.bold: true
                    }
                }
            }

            // ================= 2. 3 THẺ THỐNG KÊ =================
            RowLayout {
                Layout.fillWidth: true
                height: 110
                spacing: 18

                // Thẻ: Tiền kiếm được
                Rectangle {
                    Layout.fillWidth: true
                    height: 110
                    color: "#1B1E42"
                    radius: 18
                    border.color: "#12FFFFFF" // <--- ĐÃ SỬA LỖI RGBA

                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "TIỀN KIẾM ĐƯỢC"; color: "#8A8FC0"; font.pixelSize: 12 }
                        Text {
                            text: (typeof appController.tongThuNhap !== 'undefined' ? appController.tongThuNhap.toLocaleString('vi-VN') : "0") + " đ"
                            color: "#35DDC0"; font.pixelSize: 26; font.bold: true
                        }
                    }
                }

                // Thẻ: Số tiền đã tiêu
                Rectangle {
                    Layout.fillWidth: true
                    height: 110
                    color: "#1B1E42"
                    radius: 18
                    border.color: "#12FFFFFF" // <--- ĐÃ SỬA LỖI RGBA

                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "SỐ TIỀN ĐÃ TIÊU"; color: "#8A8FC0"; font.pixelSize: 12 }
                        Text {
                            text: (typeof appController.tongChiTieu !== 'undefined' ? appController.tongChiTieu.toLocaleString('vi-VN') : "0") + " đ"
                            color: "#F2508C"; font.pixelSize: 26; font.bold: true
                        }
                    }
                }

                // Thẻ: Số dư
                Rectangle {
                    Layout.fillWidth: true
                    height: 110
                    color: "#1B1E42"
                    radius: 18
                    border.color: "#12FFFFFF" // <--- ĐÃ SỬA LỖI RGBA

                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "SỐ DƯ"; color: "#8A8FC0"; font.pixelSize: 12 }
                        Text {
                            text: (typeof appController.soDuThang !== 'undefined' ? appController.soDuThang.toLocaleString('vi-VN') : "0") + " đ"
                            color: "#F4F5FC"; font.pixelSize: 26; font.bold: true
                        }
                    }
                }
            }

            // ================= 3. KHU VỰC BIỂU ĐỒ =================
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 18

                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    Layout.preferredWidth: 1.7
                    color: "#1B1E42"; radius: 20
                    border.color: "#12FFFFFF" // <--- ĐÃ SỬA LỖI RGBA
                    Text { anchors.centerIn: parent; text: "Chỗ của Biểu đồ tròn và MT Ngắn Hạn"; color: "#5F638F" }
                }

                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    Layout.preferredWidth: 1.0
                    color: "#1B1E42"; radius: 20
                    border.color: "#12FFFFFF" // <--- ĐÃ SỬA LỖI RGBA
                    Text { anchors.centerIn: parent; text: "Chỗ của MT Dài Hạn (Hình bình nước)"; color: "#5F638F" }
                }
            }
        }
    }
}