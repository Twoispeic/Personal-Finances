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

            // ================= 1. TOPBAR ================= (giữ nguyên)
            RowLayout {
                Layout.fillWidth: true
                ColumnLayout {
                    spacing: 4
                    Text { text: "Quản lý chi tiêu"; color: "#F4F5FC"; font.pixelSize: 26; font.bold: true }
                    Text { text: "Chi tiết các khoản chi trong tháng này"; color: "#8A8FC0"; font.pixelSize: 14 }
                }
                Item { Layout.fillWidth: true }
            }

            // ================= 2. 3 THẺ THỐNG KÊ ================= (giữ nguyên)
            RowLayout {
                Layout.fillWidth: true
                spacing: 18
                Rectangle {
                    Layout.fillWidth: true; height: 110; color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "TỔNG THU NHẬP"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                        Text { text: appController.tongThuNhap.toLocaleString('vi-VN') + " đ"; color: "#35DDC0"; font.pixelSize: 26; font.bold: true }
                    }
                }
                Rectangle {
                    Layout.fillWidth: true; height: 110; color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "TỔNG CHI TIÊU"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                        Text { text: appController.tongChiTieu.toLocaleString('vi-VN') + " đ"; color: "#F2508C"; font.pixelSize: 26; font.bold: true }
                    }
                }
                Rectangle {
                    Layout.fillWidth: true; height: 110; color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "CÒN LẠI"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                        Text { text: appController.soDuThang.toLocaleString('vi-VN') + " đ"; color: "#F4F5FC"; font.pixelSize: 26; font.bold: true }
                    }
                }
            }

            // ================= 3. KHU VỰC GRID =================
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 18

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 1.7
                    spacing: 18

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

                                Rectangle {
                                    width: 32; height: 32; radius: 16
                                    color: "#35DDC0"
                                    Text {
                                        anchors.centerIn: parent
                                        text: "+"
                                        color: "#0D111F"
                                        font.pixelSize: 18
                                        font.bold: true
                                    }
                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: themChiTieuDialog.open()
                                    }
                                }

                                Text { text: "Xem tất cả"; color: "#35DDC0"; font.pixelSize: 12; font.bold: true }
                            }

                            ListView {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                clip: true
                                spacing: 12
                                model: appController.chiTieu.danhSach

                                delegate: RowLayout {
                                    width: ListView.view.width

                                    // Màu riêng theo từng loại chi tiêu (rơi về hồng mặc định nếu thiếu)
                                    property color mauLoai: modelData.mau !== undefined ? modelData.mau : "#F2508C"

                                    Rectangle {
                                        width: 34; height: 34; radius: 10
                                        color: Qt.alpha(mauLoai, 0.15)
                                        Text { anchors.centerIn: parent; text: "?"; color: mauLoai; font.bold: true }
                                    }
                                    ColumnLayout {
                                        spacing: 2
                                        Text { text: modelData.tenLoai !== undefined ? modelData.tenLoai : "Chưa phân loại"
                                            color: "#F4F5FC"
                                            font.pixelSize: 14
                                        }
                                    }
                                    Item { Layout.fillWidth: true }
                                    Text {
                                        text: "-" + modelData.soTien.toLocaleString('vi-VN') + " đ"
                                        color: mauLoai; font.pixelSize: 14; font.bold: true
                                    }

                                    Rectangle {
                                        width: 26; height: 26; radius: 13
                                        color: Qt.alpha(mauLoai, 0.15)
                                        Text { anchors.centerIn: parent; text: "✕"; color: mauLoai; font.pixelSize: 12; font.bold: true }
                                        MouseArea {
                                            anchors.fill: parent
                                            cursorShape: Qt.PointingHandCursor
                                            onClicked: appController.chiTieu.xoa(modelData.id)
                                        }
                                    }
                                }
                            }
                        }
                    }

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
                                Text {
                                    text: appController.soDuThang.toLocaleString('vi-VN') + " đ"
                                    color: appController.soDuThang >= 0 ? "#35DDC0" : "#F2508C"
                                    font.pixelSize: 20; font.bold: true
                                }
                            }
                            Text {
                                text: "Tính từ thu nhập trừ chi tiêu tháng này"
                                color: "#5F638F"; font.pixelSize: 11
                            }
                        }
                    }
                }

                // ================= KHU VỰC BIỂU ĐỒ TRÒN & CHÚ THÍCH (XẾP DỌC) =================
                                Rectangle {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    Layout.preferredWidth: 1.0
                                    color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                                    ColumnLayout {
                                        anchors.fill: parent; anchors.margins: 24; spacing: 20

                                        Text { text: "Cơ cấu chi tiêu"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }

                                        // 1. Cục biểu đồ đẩy lên trên cùng (Đã ép cân thành hình tròn)
                                                                BieuDoTron {
                                                                    Layout.preferredWidth: 180
                                                                    Layout.preferredHeight: 180
                                                                    Layout.alignment: Qt.AlignHCenter
                                                                    modelData: appController.chiTieu.thongKeBieuDo
                                                                }


                                        // 2. Cục chú giải (Legend) nằm ngay bên dưới
                                        ColumnLayout {
                                            Layout.fillWidth: true
                                            spacing: 14

                                            Repeater {
                                                model: appController.chiTieu.thongKeBieuDo

                                                delegate: RowLayout {
                                                    // Ẩn nếu chưa có khoản chi nào thuộc loại này
                                                    visible: modelData.tongTien > 0

                                                    Layout.fillWidth: true
                                                    spacing: 8

                                                    // Chấm tròn màu
                                                    Rectangle {
                                                        width: 12; height: 12; radius: 6
                                                        color: modelData.mau
                                                    }

                                                    // Tên khoản chi
                                                    Text {
                                                        text: modelData.tenLoai + ":"
                                                        color: "#F4F5FC"
                                                        font.pixelSize: 14
                                                        Layout.fillWidth: true
                                                    }

                                                    // Số tiền
                                                    Text {
                                                        text: modelData.tongTien.toLocaleString('vi-VN') + " đ"
                                                        color: modelData.mau
                                                        font.pixelSize: 15
                                                        font.bold: true
                                                    }
                                                }
                                            }
                                        }

                                        // 3. Item tàng hình đóng vai trò như lò xo, đẩy toàn bộ nội dung dồn lên trên cho gọn
                                        Item { Layout.fillHeight: true }
                                    }
                                }
            }
        }
    }

    // Popup thêm chi tiêu — đặt ngoài cùng, cùng cấp với Item cha
    ThemChiTieuDialog {
        id: themChiTieuDialog
    }
}