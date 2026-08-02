import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    // Không dùng anchors.fill: parent ở lớp ngoài cùng để né lỗi StackView

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
                        text: "Mục tiêu tài chính"
                        color: "#F4F5FC"
                        font.pixelSize: 26
                        font.bold: true
                    }
                    Text {
                        text: "Quản lý và theo dõi tiến độ các mục tiêu của bạn"
                        color: "#8A8FC0"
                        font.pixelSize: 14
                    }
                }
            }

            // ================= 2. KHU VỰC CHIA 2 CỘT =================
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 18

                // ---------------- CỘT TRÁI: NGẮN HẠN ----------------
                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    Layout.preferredWidth: 1
                    color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 24; spacing: 16

                        Text { text: "Mục tiêu ngắn hạn (< 12 tháng)"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }

                        Text {
                            // Lấy số lượng hoàn thành từ C++
                            text: "Số mục tiêu đã hoàn thành: " + appController.mucTieu.soLuongHoanThanh
                            color: "#35DDC0"; font.pixelSize: 13
                        }

                        ListView {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            clip: true; spacing: 20
                            model: appController.mucTieu.danhSachNganHan

                            delegate: ColumnLayout {
                                width: ListView.view.width
                                spacing: 8

                                RowLayout {
                                    Layout.fillWidth: true
                                    Text { text: modelData.ten; color: "#F4F5FC"; font.pixelSize: 14 }
                                    Item { Layout.fillWidth: true }
                                    Text {
                                        // Làm tròn % tiến độ
                                        text: Math.round(modelData.tienDo) + "%"
                                        color: modelData.mauSac === "green" ? "#35DDC0" : "#F2508C"
                                        font.bold: true
                                    }
                                }

                                // Thanh tiến độ
                                Rectangle {
                                    Layout.fillWidth: true; height: 8; radius: 4; color: "#12FFFFFF"
                                    Rectangle {
                                        // Giới hạn max độ dài là 100% chiều rộng khung
                                        width: parent.width * (Math.min(modelData.tienDo, 100) / 100)
                                        height: parent.height; radius: 4
                                        // Đổi màu theo trạng thái (green = hoàn thành)
                                        color: modelData.mauSac === "green" ? "#35DDC0" : "#F2508C"
                                    }
                                }
                            }
                        }
                    }
                }

                // ---------------- CỘT PHẢI: DÀI HẠN ----------------
                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    Layout.preferredWidth: 1
                    color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"

                    ColumnLayout {
                        anchors.fill: parent; anchors.margins: 24; spacing: 16

                        Text { text: "Mục tiêu dài hạn"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }

                        ListView {
                            Layout.fillWidth: true; Layout.fillHeight: true
                            clip: true; spacing: 24
                            model: appController.mucTieu.danhSachDaiHan

                            delegate: RowLayout {
                                width: ListView.view.width
                                spacing: 20

                                // Đồ họa Tank wrap (Bình nước)
                                Item {
                                    width: 54; height: 86

                                    // Vỏ bình
                                    Rectangle {
                                        anchors.fill: parent; radius: 16
                                        color: "transparent"; border.color: "#26FFFFFF"; border.width: 2.5
                                    }

                                    // Nước bên trong
                                    Rectangle {
                                        width: parent.width - 6
                                        height: Math.max((parent.height - 6) * (Math.min(modelData.tienDo, 100) / 100), 0)
                                        anchors.bottom: parent.bottom; anchors.bottomMargin: 3
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        radius: 12
                                        color: "#6E7BFA" // Xanh dương
                                        opacity: 0.85
                                    }
                                }

                                ColumnLayout {
                                    spacing: 4
                                    Text { text: Math.round(modelData.tienDo) + "%"; color: "#6E7BFA"; font.pixelSize: 22; font.bold: true }
                                    Text { text: modelData.ten; color: "#8A8FC0"; font.pixelSize: 13 }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
}