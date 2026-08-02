import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    anchors.fill: parent
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
                    text: "Quản lý chi tiêu"
                    color: "#F4F5FC"
                    font.pixelSize: 26
                    font.bold: true
                }
                Text {
                    text: "Chi tiết các khoản chi trong tháng này"
                    color: "#8A8FC0"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            Rectangle {
                width: 44; height: 44; radius: 22
                color: "#6E7BFA"
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
            spacing: 18

            Rectangle {
                Layout.fillWidth: true; height: 110
                color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 20; spacing: 8
                    Text { text: "TỔNG THU NHẬP"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                    Text { text: appController.tongThuNhap.toLocaleString('vi-VN') + " đ"; color: "#35DDC0"; font.pixelSize: 26; font.bold: true }
                }
            }

            Rectangle {
                Layout.fillWidth: true; height: 110
                color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 20; spacing: 8
                    Text { text: "TỔNG CHI TIÊU"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                    Text { text: appController.tongChiTieu.toLocaleString('vi-VN') + " đ"; color: "#F2508C"; font.pixelSize: 26; font.bold: true }
                }
            }

            Rectangle {
                Layout.fillWidth: true; height: 110
                color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 20; spacing: 8
                    Text { text: "CÒN LẠI"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                    Text { text: appController.soDuThang.toLocaleString('vi-VN') + " đ"; color: "#F4F5FC"; font.pixelSize: 26; font.bold: true }
                }
            }
        }

        // ================= 3. KHU VỰC GRID (GIAO DỊCH & BIỂU ĐỒ) =================
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 18

            // CỘT TRÁI (1.7 phần)
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1.7
                spacing: 18

                // Thẻ: Các khoản chưa xác định
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 24
                        spacing: 16

                        RowLayout {
                            Layout.fillWidth: true
                            Text { text: "Các khoản chưa xác định"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }
                            Item { Layout.fillWidth: true }
                            Text { text: "Xem tất cả"; color: "#35DDC0"; font.pixelSize: 12; font.bold: true }
                        }

                        // Danh sách động lấy từ C++
                        ListView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            clip: true
                            spacing: 12
                            model: appController.chiTieu.danhSachChuaXacDinh

                            delegate: RowLayout {
                                width: ListView.view.width
                                Rectangle {
                                    width: 34; height: 34; radius: 10
                                    color: "#26F2508C"
                                    Text { anchors.centerIn: parent; text: "?"; color: "#F2508C"; font.bold: true }
                                }
                                ColumnLayout {
                                    spacing: 2
                                    Text { text: "Chưa phân loại"; color: "#F4F5FC"; font.pixelSize: 14 }
                                    Text { text: modelData.ngay; color: "#5F638F"; font.pixelSize: 12 }
                                }
                                Item { Layout.fillWidth: true }
                                Text {
                                    text: "-" + modelData.soTien.toLocaleString('vi-VN') + " đ"
                                    color: "#F2508C"; font.pixelSize: 14; font.bold: true
                                }
                            }
                        }
                    }
                }

                // Thẻ: Tiết kiệm tháng này
                Rectangle {
                    Layout.fillWidth: true
                    height: 90
                    color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 24; spacing: 8
                        RowLayout {
                            Layout.fillWidth: true
                            Text { text: "Đã để dành"; color: "#F4F5FC"; font.pixelSize: 14; font.bold: true }
                            Item { Layout.fillWidth: true }
                            Text { text: "1.900.000 / 3.000.000 đ"; color: "#8A8FC0"; font.pixelSize: 12 }
                        }
                        // Track nền tiến độ
                        Rectangle {
                            Layout.fillWidth: true; height: 8; radius: 4; color: "#12FFFFFF"
                            // Thanh màu chạy
                            Rectangle { width: parent.width * 0.63; height: 8; radius: 4; color: "#35DDC0" }
                        }
                    }
                }
            }

            // CỘT PHẢI (1.0 phần) - Chỗ chứa Biểu đồ tròn
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1.0
                color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                Text {
                    anchors.centerIn: parent
                    text: "Chỗ để dán code Biểu đồ tròn của Kha"
                    color: "#5F638F"
                    font.pixelSize: 14
                }
            }
        }
    }
}
}