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
                        text: "Chào " + (appController.tenNguoiDung !== "" ? appController.tenNguoiDung : "bạn") + ", cùng tiết kiệm nhé 👋"
                        color: "#F4F5FC"; font.pixelSize: 26; font.bold: true
                    }
                    Text {
                        text: "Đây là tình hình tài chính của bạn trong tháng này"
                        color: "#8A8FC0"; font.pixelSize: 14
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
                        // Gọi ID xacNhanChotSoDialog từ Main.qml
                        onClicked: xacNhanChotSoDialog.open()
                    }
                }

                Rectangle {
                    width: 44; height: 44; radius: 22
                    color: "#F2508C"
                    Text {
                        anchors.centerIn: parent
                        text: appController.tenNguoiDung !== "" ? appController.tenNguoiDung.charAt(0).toUpperCase() : "U"
                        color: "#F4F5FC"; font.pixelSize: 18; font.bold: true
                    }
                }
            }

            // ================= 2. 3 THẺ THỐNG KÊ =================
            RowLayout {
                Layout.fillWidth: true
                height: 110
                spacing: 18

                // Thẻ 1: Thu nhập
                Rectangle {
                    Layout.fillWidth: true; height: 110
                    color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "TIỀN KIẾM ĐƯỢC"; color: "#8A8FC0"; font.pixelSize: 12 }
                        Text { text: appController.tongThuNhap.toLocaleString('vi-VN') + " đ"; color: "#35DDC0"; font.pixelSize: 26; font.bold: true }
                    }
                }

                // Thẻ 2: Chi tiêu
                Rectangle {
                    Layout.fillWidth: true; height: 110
                    color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "SỐ TIỀN ĐÃ TIÊU"; color: "#8A8FC0"; font.pixelSize: 12 }
                        Text { text: appController.tongChiTieu.toLocaleString('vi-VN') + " đ"; color: "#F2508C"; font.pixelSize: 26; font.bold: true }
                    }
                }

                // Thẻ 3: Số dư
                Rectangle {
                    Layout.fillWidth: true; height: 110
                    color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 20; spacing: 8
                        Text { text: "SỐ DƯ"; color: "#8A8FC0"; font.pixelSize: 12 }
                        Text { text: appController.soDuThang.toLocaleString('vi-VN') + " đ"; color: "#F4F5FC"; font.pixelSize: 26; font.bold: true }
                    }
                }
            }

            // ================= 3. KHU VỰC BIỂU ĐỒ =================
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 18

                // --- KHỐI BÊN TRÁI (Chia 2 tầng: Tròn & Cột) ---
                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 1.7
                    spacing: 18

                    // Tầng 1: Biểu Đồ Tròn + Chú thích
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                        ColumnLayout {
                            anchors.fill: parent; anchors.margins: 20; spacing: 16
                            Text { text: "Cơ cấu chi tiêu"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }

                            RowLayout {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                spacing: 30

                                BieuDoTron {
                                    Layout.preferredWidth: 160
                                    Layout.fillHeight: true
                                    modelData: appController.chiTieu.thongKeBieuDo
                                }

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    Layout.alignment: Qt.AlignVCenter
                                    spacing: 12

                                    Repeater {
                                        model: appController.chiTieu.thongKeBieuDo
                                        delegate: RowLayout {
                                            visible: modelData.tongTien > 0
                                            Layout.fillWidth: true
                                            spacing: 8

                                            Rectangle { width: 12; height: 12; radius: 6; color: modelData.mau }
                                            Text { text: modelData.tenLoai + ":"; color: "#F4F5FC"; font.pixelSize: 14; Layout.fillWidth: true }
                                            Text { text: modelData.tongTien.toLocaleString('vi-VN') + " đ"; color: modelData.mau; font.pixelSize: 15; font.bold: true }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Tầng 2: Biểu Đồ Cột Thu Nhập
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 220
                        color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                        ColumnLayout {
                            anchors.fill: parent; anchors.margins: 20; spacing: 16
                            Text { text: "Thu nhập 12 tháng qua"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }

                            Row {
                                Layout.fillWidth: true; Layout.fillHeight: true
                                spacing: 12

                                Repeater {
                                    model: appController.thuNhap.thongKe12Thang
                                    delegate: Item {
                                        width: 32
                                        height: parent.height

                                        function getMaxTien() {
                                            let max = 0;
                                            let dataList = appController.thuNhap.thongKe12Thang;
                                            for(let i=0; i<dataList.length; i++) {
                                                if(dataList[i].soTien > max) max = dataList[i].soTien;
                                            }
                                            return max === 0 ? 1 : max;
                                        }

                                        Rectangle {
                                            width: 18
                                            height: (modelData.soTien / getMaxTien()) * 120
                                            anchors.bottom: txtThang.top; anchors.bottomMargin: 8
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            color: modelData.soTien > 0 ? "#6E7BFA" : "#12FFFFFF"
                                            radius: 6
                                        }

                                        Text {
                                            id: txtThang
                                            text: modelData.thang.split("/")[0]
                                            color: "#5F638F"; font.pixelSize: 12; font.bold: true
                                            anchors.bottom: parent.bottom
                                            anchors.horizontalCenter: parent.horizontalCenter
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // --- KHỐI BÊN PHẢI (Mục tiêu tài chính - Có Toggle gạt) ---
                                Rectangle {
                                    id: rightBlock
                                    Layout.fillWidth: true; Layout.fillHeight: true
                                    Layout.preferredWidth: 1.0
                                    color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                                    // Biến theo dõi đang ở trang nào (0: Ngắn hạn, 1: Dài hạn)
                                    property int currentTabIndex: 0

                                    ColumnLayout {
                                        anchors.fill: parent
                                        anchors.margins: 20
                                        spacing: 20

                                        // 1. THANH GẠT (TOGGLE BAR)
                                        Rectangle {
                                            Layout.fillWidth: true
                                            height: 44
                                            radius: 12
                                            color: "#0D111F" // Màu nền chìm bên dưới

                                            RowLayout {
                                                anchors.fill: parent
                                                anchors.margins: 4
                                                spacing: 4

                                                // Nút: Ngắn hạn
                                                Rectangle {
                                                    Layout.fillWidth: true; Layout.fillHeight: true
                                                    radius: 10
                                                    color: rightBlock.currentTabIndex === 0 ? "#35DDC0" : "transparent"

                                                    Text {
                                                        anchors.centerIn: parent
                                                        text: "Mục tiêu ngắn hạn"
                                                        color: rightBlock.currentTabIndex === 0 ? "#0D111F" : "#8A8FC0"
                                                        font.pixelSize: 14; font.bold: true
                                                    }
                                                    MouseArea {
                                                        anchors.fill: parent; cursorShape: Qt.PointingHandCursor
                                                        onClicked: rightBlock.currentTabIndex = 0
                                                    }
                                                }

                                                // Nút: Dài hạn
                                                Rectangle {
                                                    Layout.fillWidth: true; Layout.fillHeight: true
                                                    radius: 10
                                                    color: rightBlock.currentTabIndex === 1 ? "#35DDC0" : "transparent"

                                                    Text {
                                                        anchors.centerIn: parent
                                                        text: "Mục tiêu dài hạn"
                                                        color: rightBlock.currentTabIndex === 1 ? "#0D111F" : "#8A8FC0"
                                                        font.pixelSize: 14; font.bold: true
                                                    }
                                                    MouseArea {
                                                        anchors.fill: parent; cursorShape: Qt.PointingHandCursor
                                                        onClicked: rightBlock.currentTabIndex = 1
                                                    }
                                                }
                                            }
                                        }

                                        // 2. KHU VỰC HIỂN THỊ NỘI DUNG (LẬT TRANG)
                                        StackLayout {
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            currentIndex: rightBlock.currentTabIndex // Liên kết với thanh gạt ở trên

                                            // --- TRANG 0: NGẮN HẠN (Progress Bar ngang) ---
                                            ScrollView {
                                                Layout.fillWidth: true; Layout.fillHeight: true
                                                clip: true

                                                ColumnLayout {
                                                    width: parent.width; spacing: 20

                                                    Repeater {
                                                        model: appController.mucTieu.danhSachNganHan
                                                        delegate: ColumnLayout {
                                                            Layout.fillWidth: true; spacing: 8

                                                            RowLayout {
                                                                Layout.fillWidth: true
                                                                Text { text: modelData.ten; color: "#F4F5FC"; font.pixelSize: 14; font.bold: true }
                                                                Item { Layout.fillWidth: true }
                                                                Text {text: Math.min(100, (modelData.soTienDaTietKiem / modelData.soTienMucTieu * 100)).toFixed(2) + "%"
                                                                      color: "#35DDC0"; font.pixelSize: 14; font.bold: true}
                                                            }

                                                            // Thanh tiến trình
                                                            Rectangle {
                                                                Layout.fillWidth: true; height: 8; radius: 4; color: "#0D111F"
                                                                Rectangle {
                                                                    // Tính toán độ dài phần trăm
                                                                    width: parent.width * Math.min(1.0, (modelData.soTienDaTietKiem / (modelData.soTienMucTieu > 0 ? modelData.soTienMucTieu : 1)))
                                                                    height: parent.height; radius: 4; color: "#35DDC0"
                                                                }
                                                            }

                                                            Text {
                                                                text: modelData.soTienDaTietKiem.toLocaleString('vi-VN') + " / " + modelData.soTienMucTieu.toLocaleString('vi-VN') + " đ"
                                                                color: "#8A8FC0"; font.pixelSize: 12
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                            // --- TRANG 1: DÀI HẠN (Lọ thủy tinh xếp dọc) ---
                                            ScrollView {
                                                Layout.fillWidth: true; Layout.fillHeight: true
                                                clip: true

                                                ColumnLayout {
                                                    width: parent.width; spacing: 24

                                                    Repeater {
                                                        model: appController.mucTieu.danhSachDaiHan
                                                        delegate: RowLayout {
                                                            Layout.fillWidth: true; spacing: 16

                                                            // Vẽ cái Lọ Thủy Tinh
                                                            Rectangle {
                                                                width: 44; height: 70
                                                                radius: 8
                                                                color: "#0D111F"
                                                                border.color: "#35DDC0"; border.width: 1.5
                                                                clip: true

                                                                // Nước dâng lên từ đáy lọ
                                                                Rectangle {
                                                                    width: parent.width
                                                                    height: parent.height * Math.min(1.0, (modelData.soTienDaTietKiem / (modelData.soTienMucTieu > 0 ? modelData.soTienMucTieu : 1)))
                                                                    anchors.bottom: parent.bottom
                                                                    color: "#35DDC0"
                                                                    opacity: 0.8
                                                                }
                                                                // Nắp lọ cho chân thực
                                                                Rectangle {
                                                                    width: 24; height: 4; color: "#8A8FC0"
                                                                    anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter
                                                                }
                                                            }

                                                            // Thông tin bên cạnh lọ thủy tinh
                                                            ColumnLayout {
                                                                Layout.fillWidth: true; spacing: 4
                                                                Text { text: modelData.ten; color: "#F4F5FC"; font.pixelSize: 15; font.bold: true }
                                                                Text {
                                                                    text: modelData.soTienDaTietKiem.toLocaleString('vi-VN') + " đ"
                                                                    color: "#35DDC0"; font.pixelSize: 14; font.bold: true
                                                                }
                                                                Text {
                                                                    text: "Mục tiêu: " + modelData.soTienMucTieu.toLocaleString('vi-VN') + " đ"
                                                                    color: "#8A8FC0"; font.pixelSize: 12
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } // End StackLayout
                                    }
                                }
            }
        }
    }
}