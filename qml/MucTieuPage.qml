import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    Item {
        anchors.fill: parent
        Item {
            anchors.fill: parent
            anchors.margins: 40

            ColumnLayout {
                anchors.fill: parent
                spacing: 28

                // TOPBAR + nút "+"
                RowLayout {
                    Layout.fillWidth: true
                    ColumnLayout {
                        spacing: 4
                        Text { text: "Mục tiêu tài chính"; color: "#F4F5FC"; font.pixelSize: 26; font.bold: true }
                        Text { text: "Quản lý và theo dõi tiến độ các mục tiêu của bạn"; color: "#8A8FC0"; font.pixelSize: 14 }
                    }
                    Item { Layout.fillWidth: true }

                    Rectangle {
                        width: 40; height: 40; radius: 20
                        color: "#35DDC0"
                        Text { anchors.centerIn: parent; text: "+"; color: "#0D111F"; font.pixelSize: 22; font.bold: true }
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: taoMucTieuDialog.open()
                        }
                    }
                }

                // Thẻ tổng tiết kiệm
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 18

                    Rectangle {
                        Layout.fillWidth: true; height: 90
                        color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                        ColumnLayout {
                            anchors.fill: parent; anchors.margins: 20; spacing: 6
                            Text { text: "TIẾN ĐỘ TỔNG MỤC TIÊU"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                            Text {
                                text: appController.mucTieu.tongDaTietKiem.toLocaleString('vi-VN') + " / "
                                    + appController.mucTieu.tongMucTieu.toLocaleString('vi-VN') + " đ"
                                color: "#35DDC0"; font.pixelSize: 22; font.bold: true
                            }
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true; height: 90
                        color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                        ColumnLayout {
                            anchors.fill: parent; anchors.margins: 20; spacing: 6
                            Text { text: "HŨ TIẾT KIỆM KHẢ DỤNG"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                            Text {
                                text: appController.huTietKiem.toLocaleString('vi-VN') + " đ"
                                color: "#FFB35C"; font.pixelSize: 22; font.bold: true
                            }
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 18

                    // CỘT NGẮN HẠN
                    Rectangle {
                        Layout.fillWidth: true; Layout.fillHeight: true
                        color: "#1B1E42"; radius: 20; border.color: "#12FFFFFF"
                        ColumnLayout {
                            anchors.fill: parent; anchors.margins: 24; spacing: 16
                            Text { text: "Mục tiêu ngắn hạn (< 12 tháng)"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }
                            Text {
                                text: "Số mục tiêu đã hoàn thành: " + appController.mucTieu.soLuongHoanThanh
                                color: "#35DDC0"; font.pixelSize: 13
                            }

                            ListView {
                                Layout.fillWidth: true; Layout.fillHeight: true
                                clip: true; spacing: 20
                                model: appController.mucTieu.danhSachNganHan

                                delegate: ColumnLayout {
                                    width: ListView.view.width
                                    spacing: 6

                                    RowLayout {
                                        Layout.fillWidth: true
                                        Text { text: modelData.ten; color: "#F4F5FC"; font.pixelSize: 14; font.bold: true }
                                        Item { Layout.fillWidth: true }
                                        Text {
                                            text: Math.round(modelData.tienDo) + "%"
                                            color: modelData.mauSac === "green" ? "#35DDC0" : "#F2508C"
                                            font.bold: true
                                        }
                                    }

                                    Text {
                                        text: "Đã tiết kiệm: " + modelData.soTienDaTietKiem.toLocaleString('vi-VN')
                                            + " / " + modelData.soTienMucTieu.toLocaleString('vi-VN') + " đ"
                                        color: "#8A8FC0"; font.pixelSize: 12
                                    }
                                    Text {
                                        text: "Thời hạn: " + modelData.thoiHanThang + " tháng"
                                        color: "#5F638F"; font.pixelSize: 12
                                    }

                                    Rectangle {
                                        Layout.fillWidth: true; height: 8; radius: 4; color: "#12FFFFFF"
                                        Rectangle {
                                            width: parent.width * (Math.min(modelData.tienDo, 100) / 100)
                                            height: parent.height; radius: 4
                                            color: modelData.mauSac === "green" ? "#35DDC0" : "#F2508C"
                                        }
                                    }

                                    Rectangle {
                                        visible: modelData.mauSac !== "green"
                                        Layout.preferredWidth: 100
                                        Layout.preferredHeight: 28
                                        radius: 8
                                        color: "#35DDC0"
                                        Text {
                                            anchors.centerIn: parent
                                            text: "Nộp tiền"
                                            color: "#0D111F"; font.pixelSize: 12; font.bold: true
                                        }
                                        MouseArea {
                                            anchors.fill: parent
                                            cursorShape: Qt.PointingHandCursor
                                            onClicked: {
                                                gopTietKiemDialog.mucTieuId = modelData.id
                                                gopTietKiemDialog.tenMucTieu = modelData.ten
                                                gopTietKiemDialog.soTienConDu = appController.huTietKiem   // đổi ở đây
                                                gopTietKiemDialog.open()
                                            }
                                        }
                                    }
                                    Rectangle {
                                                width: 26
                                                height: 26
                                                radius: 13
                                                color: "#26F2508C" // Màu nền nhẹ cho nút xóa (đỏ hồng mờ)
                                                Layout.alignment: Qt.AlignVCenter

                                                Text {
                                                    anchors.centerIn: parent
                                                    text: "✕"
                                                    color: "#F2508C"
                                                    font.bold: true
                                                    font.pixelSize: 12
                                                }

                                                MouseArea {
                                                    anchors.fill: parent
                                                    cursorShape: Qt.PointingHandCursor
                                                    onClicked: {
                                                        // Gọi hàm xóa theo đúng ID của mục tiêu trên hàng này
                                                        appController.mucTieu.xoa(modelData.id)
                                                    }
                                                }
                                        }
                                }
                            }
                        }
                    }

                    // CỘT DÀI HẠN
                    // CỘT DÀI HẠN
                    Rectangle {
                        Layout.fillWidth: true;
                        Layout.fillHeight: true
                        color: "#1B1E42";
                        radius: 20; border.color: "#12FFFFFF"

                        ColumnLayout {
                            anchors.fill: parent;
                            anchors.margins: 24; spacing: 16

                            // HEADER: Bọc riêng vào RowLayout để chống đè chữ (overlap)
                            RowLayout {
                                Layout.fillWidth: true

                                ColumnLayout {
                                    spacing: 4
                                    Text { text: "Mục tiêu dài hạn"; color: "#F4F5FC"; font.pixelSize: 16; font.bold: true }
                                    Text { text: "Tự động trích tiền từ hũ tiết kiệm mỗi khi bấm refresh"; color: "#5F638F"; font.pixelSize: 11 }
                                }

                                Item { Layout.fillWidth: true } // Đẩy nút sang phải

                                Rectangle {
                                    width: 32; height: 32; radius: 16
                                    color: "#6E7BFA"
                                    Text { anchors.centerIn: parent; text: "⟳"; color: "#FFF"; font.pixelSize: 16; font.bold: true }

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        // GỌI HÀM MỚI Ở ĐÂY: Chỉ phân bổ tiền hũ, không reset tháng
                                        onClicked: appController.lamMoiMucTieu()
                                    }
                                }
                            }

                            // LISTVIEW: Danh sách các thẻ mục tiêu
                            ListView {
                                Layout.fillWidth: true;
                                Layout.fillHeight: true
                                clip: true;
                                spacing: 24
                                model: appController.mucTieu.danhSachDaiHan

                                delegate: RowLayout {
                                    width: ListView.view.width
                                    spacing: 20

                                    Item {
                                        width: 54;
                                        height: 86
                                        Rectangle {
                                            anchors.fill: parent;
                                            radius: 16
                                            color: "transparent";
                                            border.color: "#26FFFFFF"; border.width: 2.5
                                        }
                                        Rectangle {
                                            width: parent.width - 6
                                            height: Math.max((parent.height - 6) * (Math.min(modelData.tienDo, 100) / 100), 0)
                                            anchors.bottom: parent.bottom;
                                            anchors.bottomMargin: 3
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            radius: 12
                                            color: "#6E7BFA"
                                            opacity: 0.85
                                        }
                                    }

                                    ColumnLayout {
                                        spacing: 4
                                        Text { text: modelData.ten; color: "#F4F5FC"; font.pixelSize: 14; font.bold: true }
                                        Text { text: Math.round(modelData.tienDo) + "%"; color: "#6E7BFA"; font.pixelSize: 18; font.bold: true }
                                        Text {
                                            text: "Đã tiết kiệm: " + modelData.soTienDaTietKiem.toLocaleString('vi-VN')
                                                    + " / " + modelData.soTienMucTieu.toLocaleString('vi-VN') + " đ"
                                            color: "#8A8FC0";
                                            font.pixelSize: 12
                                        }
                                        Text {
                                            text: "Đã trả: " + modelData.soKyDaTra + " / " + modelData.soKyTraGop + " tháng"
                                            color: "#5F638F";
                                            font.pixelSize: 12
                                        }
                                    }
                                    Rectangle {
                                                width: 26
                                                height: 26
                                                radius: 13
                                                color: "#26F2508C" // Màu nền nhẹ cho nút xóa (đỏ hồng mờ)
                                                Layout.alignment: Qt.AlignVCenter

                                                Text {
                                                    anchors.centerIn: parent
                                                    text: "✕"
                                                    color: "#F2508C"
                                                    font.bold: true
                                                    font.pixelSize: 12
                                                }

                                                MouseArea {
                                                    anchors.fill: parent
                                                    cursorShape: Qt.PointingHandCursor
                                                    onClicked: {
                                                        // Gọi hàm xóa theo đúng ID của mục tiêu trên hàng này
                                                        appController.mucTieu.xoa(modelData.id)
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
    }

    TaoMucTieuDialog {
        id: taoMucTieuDialog
    }
    GopTietKiemDialog {
        id: gopTietKiemDialog
    }
}