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
                Rectangle {
                    width: 44; height: 44; radius: 22; color: "#6E7BFA"
                    Text {
                        anchors.centerIn: parent
                        text: appController.tenNguoiDung !== "" ? appController.tenNguoiDung.charAt(0).toUpperCase() : "U"
                        color: "#F4F5FC"; font.pixelSize: 18; font.bold: true
                    }
                }
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

                                    Rectangle {
                                        width: 26; height: 26; radius: 13
                                        color: "#26F2508C"
                                        Text { anchors.centerIn: parent; text: "✕"; color: "#F2508C"; font.pixelSize: 12; font.bold: true }
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
                                    text: appController.mucTieu.tongDaTietKiem.toLocaleString('vi-VN') + " / "
                                        + appController.mucTieu.tongMucTieu.toLocaleString('vi-VN') + " đ"
                                    color: "#8A8FC0"; font.pixelSize: 12
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true; height: 8; radius: 4; color: "#12FFFFFF"
                                Rectangle {
                                    width: parent.width * (appController.mucTieu.tongMucTieu > 0
                                        ? appController.mucTieu.tongDaTietKiem / appController.mucTieu.tongMucTieu : 0)
                                    height: 8; radius: 4; color: "#35DDC0"
                                }
                            }
                        }
                    }
                }

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

    // Popup thêm chi tiêu — đặt ngoài cùng, cùng cấp với Item cha
    ThemChiTieuDialog {
        id: themChiTieuDialog
    }
}